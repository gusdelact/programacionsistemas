/*Proceso mediador para manipuolar comunicacion publish & suscribe*/

#include  <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

#define PIPESUSCRIBE "/tmp/psuscribe"
#define PIPEPUBLISH "/tmp/ppublish"
#define MAXLEN 1024
#define MAXSUSCRITOS 128

/*numero suscriptores*/
int nSuscriptores;

/*variable global para definir extremos de comunicacion entre
proceso suscriptor y publicador */

int internalPipe[2];

/*estructura de datos que define mensaje del suscriptor*/

struct mensajeSuscriptor {
	int pid; /*indica el PID del proceso suscriptor*/
};

struct mensajePublicador {
	char mensaje[MAXLEN]; /* se escribe un mensaje de cualquier tipo de
				datos*/
};

struct suscrito {
	int pid; /* identificador de proceso*/
	char pipe[128]; /*pipe donde toma el mensaje del publicador*/ 
};

struct suscrito lista[MAXSUSCRITOS]; /*lista suscritos*/
 
void finalizaPublicador(int signo) {
	int i;
	printf("Recibiendo signal %d\n",signo);

	unlink(PIPEPUBLISH);
	for (i=0;i<nSuscriptores ;i++) {
		unlink(lista[i].pipe);
	}
	/*se mata a si mismo*/
	printf("Fin de servidor de publicacion\n");
	exit(0);
}

void procesaSuscripcion() {
	
	int fd,rtn;
	int nbytes;
	int pid;
	struct mensajeSuscriptor mensaje; /*estructura para leer mensaje
					suscriptor*/
	int i=0;
	
	/* no utiliza extremo de lectura de pipe Interno*/
	close(internalPipe[0]);
	while (i<nSuscriptores) {
		/*pipe de suscripcion se abre de lectura*/
		printf("Esperando suscriptores...\n");
		fd=open(PIPESUSCRIBE,O_RDONLY);	

		if (fd < 0) {
			perror("Error al abrir pipe suscripcion");
			exit(4);
		}/*if*/
		/*esperar un mensaje sobre el pipe de suscripcion*/	

		nbytes= read(fd, &mensaje, sizeof(mensaje));

		if (nbytes < 0) {
			perror("error al leer mensaje suscriptor");
			continue; /*ignorar al suscriptor*/
		}

		pid= mensaje.pid;
	
		nbytes=	
		write(internalPipe[1],&pid,sizeof(int));
		i++; /*incrementar el numero de suscritos*/	

		/*se cierra el pipe*/
		close(fd);
		printf("Faltan %d suscriptores", nSuscriptores-i);
	} /*while*/
	close(internalPipe[1]);
	printf("Todos estan suscritos\n");
}

void procesaPublicacion(){
	int fd,rtn;
	int nbytes;
	int i=0;

	struct sigaction accion;

	/*manejar fin de servicio con SIGGUP*/
	accion.sa_handler=finalizaPublicador ;
	sigemptyset(&accion.sa_mask); /*no se bloque ninguna sennal*/
	accion.sa_flags = 0;

	sigaction(SIGHUP,&accion,(struct sigaction *) 0);
	/* no utiliza extremo de escritura de pipe Interno*/

	close(internalPipe[1]);
	while ( i <  nSuscriptores) {
		read(internalPipe[0],&(lista[i].pid),sizeof(lista[i].pid));
		i++;
	} /*while*/
	close(internalPipe[0]);
	
	for (i=0;i<nSuscriptores;i++) {
		char nombrePipe[128];

		sprintf(nombrePipe,"/tmp/p%d",lista[i].pid);

		strcpy(lista[i].pipe,nombrePipe);
		rtn=mknod(lista[i].pipe,S_IFIFO|0666,0);

		if (rtn< 0) {
			perror("Error al crear pipe de mensaje");
		}
		printf("Proceso inscrito %d\n",lista[i].pid);
	} /*for*/

	while (1) {
		struct mensajePublicador mensaje;
		printf("Esperando publicadores...\n");
		fd= open(PIPEPUBLISH,O_RDONLY);

		if (fd < 0) {
			printf("Error al abrir pipe de publicacion");
		} /*if*/

		nbytes=read(fd,&mensaje ,sizeof(mensaje));

		if (nbytes < 0) {
			perror("error al comunicarse con publicador");
			continue; /*ignorar*/
		} else {
			int fd2;

			/*enviar un signal a cada proceso*/

			for (i=0 ;i < nSuscriptores;i++) {
				/*enviando signal a cada proceso inscrito*/
				rtn=kill(lista[i].pid  ,SIGTERM);

				if (rtn < 0) {
					perror("error al enviar signal");
				} else {
					printf("Enviando signal a %d \n",lista[i].pid);
					printf("Enviando mensaje a %d %s\n",lista[i].pid,lista[i].pipe);
				 	fd2=open(lista[i].pipe,O_WRONLY);
					
					if (fd2< 0) {
						perror("Error al abir pipe de mensajes");
					} else {
						nbytes=
						write(fd2,mensaje.mensaje,strlen(mensaje.mensaje));
						if (nbytes < 0) {
							perror("error al escribir pipe de mensaje");
						} /*if*/
						close(fd2);
					} /*else*/
				} /*if*/
			} /*for*/
			close(fd);
		}/*else*/
	} /*while*/
}

void creaServidorSuscripcion(void){
	int pid;

	pid=fork();
	if (pid < 0) {
		exit(3);
	} else if (pid == 0) {
		procesaSuscripcion();
		printf("Fin servidor suscripcion");
		unlink(PIPESUSCRIBE );
		exit(0);
	} else {
		printf("Servidor suscripcion con PID %d \n",pid);
	}
}

void creaServidorPublicacion(){
	int pid;
	pid=fork();

	if (pid < 0) {
		exit(3);
	} else if (pid == 0) {
		procesaPublicacion();
		printf("Fin servidor publicacion");
		unlink(PIPEPUBLISH );
		exit(0);
	} else {
		printf("Servidor publicacion con PID %d \n",pid);
	}
}

main(int argc, char * argv []) {

	int rtn;

	if (argc<=1) {
		printf("Ejemplo17 numeroParticipantes");
		exit(1);
	}

	nSuscriptores=atoi(argv[1]);

	/*crear los dos pipes , utilizando mknod */

	rtn= mknod(PIPESUSCRIBE,S_IFIFO|0666,0);

	if (rtn < 0) {
		perror("Error al crear pipe de suscripcion");
		exit(1);
	}	    

	rtn= mknod(PIPEPUBLISH,S_IFIFO|0666,0);

	if (rtn < 0) {
		perror("Error al crear pipe de publicacion");
		exit(2);
	}


	/*Crea el pipe de comunicacion entre proceso suscripcion
	y publicador*/

	rtn= pipe(internalPipe);

	if (rtn < 0) {
		perror("Error al crear pipe de comunicacion interna");
	}
	/* Este proceso va a crear dos hijos (demonios), para
	   esperar la suscripcion y otro para publicacion de eventos*/
	creaServidorSuscripcion();
	creaServidorPublicacion();

	/*el proceso padre cierra el pipe, no lo necesita*/
	close(internalPipe[0]);
	close(internalPipe[1]);
	printf("Servicio Publish & Suscribe Inicializado\n");  	  
	exit(0);
}	
