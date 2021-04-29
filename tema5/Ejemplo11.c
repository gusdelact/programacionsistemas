#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc, char * argv[]) {

	int fd[2];
	int nbytes,j;
	char mensaje[]="hola\n";

	if (argc <= 2) {
		printf("Ejemplo11 rutaFIFOin rutaFIFOout \n");
		exit(1);
	}


	/*Abrir de escritura al pipe*/

	fd[0]=open(argv[1],O_WRONLY);

	if (fd[0]< 0) {
		perror("Error al abrir el named pipe de escritura");
		exit(2);
	}

	fd[1]=open(argv[2],O_RDONLY);
	if (fd[1]< 0) {
		perror("Error al abrir el named pipe de lectura");
		exit(2);
	}

	nbytes=write(fd[0],mensaje,strlen(mensaje));

	if (nbytes < 0) {
		perror("Error al escribir el named pipe de escritura");
		exit(3);
	}

	printf("PID %d escribiendo %d bytes\n",getpid(), nbytes);

	nbytes=read(fd[1],mensaje,128);

	if (nbytes< 0) {
		perror("Error al leer el named pipe de lectura");
		exit(4);
	}
	mensaje[nbytes]=0;

	printf("PID %d leyendo %d bytes %s\n",getpid(), nbytes,mensaje);

	close(fd[0]);
	close(fd[1]);

	exit(0);
}

