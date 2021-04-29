#include  <unistd.h>
#include  <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define PIPESUSCRIBE "/tmp/psuscribe"
struct mensajeSuscriptor {
        int pid; /*indica el PID del proceso suscriptor*/
};

void suscribe(char * argv[]) {
	int fd;
	int nbytes; 
	int rtn;

	struct mensajeSuscriptor mensaje; 

	fd=open(PIPESUSCRIBE,O_WRONLY);
	mensaje.pid=getpid();

	nbytes=
	write(fd,&mensaje,sizeof(mensaje));

	if (nbytes <0) {
		printf("error al suscribir el proceso\n");
	} else {
		printf("Inscrito proceso %d",getpid());
	}

	close(fd);

	printf(argv[0]);
	rtn=execvp(argv[0],&argv[0]);

	if (rtn< 0) {
		perror("error al ejecutar programa");
		exit(2);
	}
}

main(int argc, char * argv[]) {

	if ( argc <=1) {
		printf("Ejemplo18 programa");
		exit(1);
	}	
	suscribe(&argv[1]);
}
