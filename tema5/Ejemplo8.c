#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc, char * argv[]) {

	int fd;
	int nbytes,j;
	char mensaje[]="hola\n";

	if (argc <= 1) {
		printf("Ejemplo7 rutaFIFO \n");
		exit(1);
	}


	/*Abrir de escritura al pipe*/

	fd=open(argv[1],O_WRONLY);

	if (fd< 0) {
		perror("Error al abrir el named pipe");
		exit(2);
	}

	nbytes=write(fd,mensaje,strlen(mensaje));

	if (nbytes < 0) {

	}

	printf("PID %d escribiendo %d bytes\n",getpid(), nbytes);
	close(fd);

	exit(0);
}

