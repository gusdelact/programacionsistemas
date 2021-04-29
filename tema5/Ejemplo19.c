#include  <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>


int i=0;

void procesarEvento(int signo) {
	int fd,nbytes;
	char buffer[128];
	char nombrePipe[128];

	printf("Signal Evento %d\n",signo);
	printf("Valor de i=%d\n",i);

	sprintf(nombrePipe,"/tmp/p%d",getpid());
	fd= open(nombrePipe,O_RDONLY);

	if (fd < 0) {
		perror("No puedo abrir pipe de mensajes");
	} else {
		nbytes=read(fd,buffer,128); 

		if (nbytes < 0) {
			perror("No puedo abrir pipe de mensajes");
		} else {
			buffer[nbytes]=0;
			printf("%s\n",buffer);
		}
		close(fd);	
	}
}

main() {

	struct sigaction nuevaAccion;
	int rtn,x;
	char * ptr=0;

	/*Llenar la estructura sigaction*/
	nuevaAccion.sa_handler= procesarEvento; 
	sigemptyset(&nuevaAccion.sa_mask); /*no se bloque ninguna sennal*/
	nuevaAccion.sa_flags=0; /*no hay banderas*/

	rtn=sigaction(SIGTERM,&nuevaAccion,(struct sigaction *)0);
	
	if (rtn < 0) {
		perror("Error al registar manejador de signal");
		exit(1);
	}


	while (1) {
		i++;
	}
}
