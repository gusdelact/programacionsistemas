#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc, char * argv[]) {

	int rtn;
	int fd;
	int nbytes,j;
	char mensaje[128];

	if (argc <= 1) {
		printf("Ejemplo7 rutaFIFO \n");
		exit(1);
	}

	/*Indica al kernel que debe crear un archivo de tipo PIPE
	  El segundo parametro es una mascar de bits.
	  Se efectua una operacion OR de bits para indicar que
	  es un FIFO y que los permisos son de lectura/escritura
	  propietario, lectura para grupo y lectura para otros
	*/
	rtn= mknod(argv[1],S_IFIFO | 0644, 0);

	if (rtn < 0) {

		perror("Error al crear el named pipe");
		exit(1);
	}

	/*obtener el descriptor de archivo de lectura*/
	printf("PID %d Esperando el mensaje\n", getpid());
	fd= open(argv[1],O_RDONLY);	

	if (fd < 0) {
		perror("Error al abrir extremo de lectura del pipe");
	}

	printf("PID %d un proceso cliente tiene un mensaje, a leer\n", getpid());

	/*leer el named pipe*/
	nbytes= read(fd,mensaje,128);
	
	if (nbytes<=0) {
		perror("Error al leer el named pipe");
		exit(2);
	}

	mensaje[nbytes]=0;	
	printf("Leyendo %d bytes %s\n",nbytes,mensaje);

	for(j=0;j<strlen(mensaje);j++) {
        	mensaje[j]=toupper(mensaje[j]);
        }

	printf("proceso %d convierte mensaje %s\n", getpid(),mensaje);

	close(fd);

	/*borrar el named pipe*/	
	unlink(argv[1]);

	exit(0);
}
