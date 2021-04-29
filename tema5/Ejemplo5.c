/*Ejemplo5 Pone en un solo archivo varios archivos y directorios
y los comprime*/

#include <unistd.h>

/*este es el comando tar cvf - */
char  comando1[]= "/bin/tar";
char  arcmd1[]="-cvf";
char  arcmd2[]="-";
char  comando2[]= "/usr/bin/compress";
/*esto tambien se hubiera realizado con directivas define y
sin usar variables globales*/

void juntar(char ** lista,int numArchs) {
	char * args[1024];
	int limit=numArchs+2;
	int i,rtn;

	args[0]=comando1;
	args[1]=arcmd1;
	args[2]=arcmd2;

	for (i=0;i< numArchs; i++) {
		args[i+3]= lista[i];
		if ( (i+1 ) >= 1023 ) {
			limit=1022;
			break;
		}
	}

	args[limit+1]= (char *) 0;
	
	
	rtn=execv(comando1,args);

	if (rtn < 0) {
		perror("Error en execv tar");
		exit(5);
	}

}

void comprimir( char * archivo) {
	int rtn;
	int fd;

	fd= creat(archivo,0640);

	if (fd < 0) {
		perror("Error en creat");
		exit(5);
	}

	rtn= dup2(fd,1);

	if (rtn<0) {
		perror("Error en dup2");
		exit(5);
	}
	close(fd);

	rtn=
	execl(comando2,comando2, (char * )0);

	if (rtn < 0) {
		perror("Error en execl compress");
		exit(5);
	}
}

int main(int argc, char * argv[]) {

	int rtn,i;
	int pipefd[2];
	char * destino;
	char ** listaArchivos;
	if (argc <= 3) {
		printf("Ejemplo5 destino lista-archivos ...\n");
		exit(1);
	}

	destino=argv[1];
	listaArchivos= &argv[2];

	rtn= pipe(pipefd);		

	if (rtn < 0) {
		perror("Error al crear pipe");
		exit(2);
	}

	for (i=0;i<=1;i++) {

		rtn= fork();

		if (rtn < 0) {
			perror("Error en fork");
			exit(3);
		}

		if (rtn == 0) {
			if (i==0) {

				/*direccionar la salida estandar
				al pipe de escritura*/
				rtn= dup2(pipefd[1],1 ) ;

				if (rtn < 0) {
					perror("Error al redireccionar pipe");
					exit(4);
				} 
				/*cerrar pipe de escritura*/
				/*cerrar el extremo de lectura del pipe*/
				close(pipefd[0]);
				close(pipefd[1]);
				/*invocar comando tar*/
				juntar(listaArchivos,argc-2);
				exit(0);
			} else if (i==1) {

				/*direccionar la entrada estandar
				al extremo de lectura del pipe*/
				rtn= dup2(pipefd[0],0 ) ;
				if (rtn < 0) {
					perror("Error al redireccionar pipe");
					exit(4);
				}
				close(pipefd[0]);
				/*cerrar el extremo de escritura del pipe*/
				close(pipefd[1]);
				comprimir(destino);
				exit(0);
			}
		} 
	}

	/*el proceso padre debe liberar los extremos del pipe*/
	close(pipefd[0]);
	/*cerrar el extremo de escritura del pipe*/
	close(pipefd[1]);
	for (i=0;i<2;i++){
		wait((int *) 0);
	}
	exit(0);	
}
