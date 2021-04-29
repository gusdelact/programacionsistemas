#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc, char * argv[]) {

	int rtn;
	int fd[2];
	int nbytes,j;
	char mensaje[128];

	if (argc <= 2) {
		printf("Ejemplo10 rutaFIFOIn rutaFIFOOut \n");
		exit(1);
	}

	/*Indica al kernel que debe crear un archivo de tipo PIPE
	  El segundo parametro es una mascara de bits.
	  Se efectua una operacion OR de bits para indicar que
	  es un FIFO y que los permisos son de lectura/escritura
	  propietario, lectura para grupo y lectura para otros
	*/
	rtn= mknod(argv[1],S_IFIFO | 0644, 0);

	if (rtn < 0) {
		perror("Error al crear el named pipe de lectura");
		exit(1);
	}

	/*Indica al kernel que debe crear un archivo de tipo PIPE
	  El segundo parametro es una mascara de bits.
	  Se efectua una operacion OR de bits para indicar que
	  es un FIFO y que los permisos son de lectura/escritura
	  propietario, lectura para grupo y lectura para otros
	*/
	rtn=mknod(argv[2],S_IFIFO | 0644,0);
	if (rtn < 0) {
		perror("Error al crear el named pipe de escritura");
		exit(1);
	}
	

	/*obtener el descriptor de archivo de lectura*/
	printf("PID %d Bloquado en open %s para lectura\n", getpid(),argv[1]);
	fd[0]= open(argv[1],O_RDONLY);	

	if (fd < 0) {
		perror("Error al abrir extremo de lectura del pipe");
	}

		


	printf("PID %d Bloquado en open %s para escritura\n", getpid(),argv[2]);
	fd[1]=open(argv[2],O_WRONLY);

	printf("PID %d un proceso cliente tiene un mensaje, a leer\n", getpid());

	/*leer el named pipe*/
	nbytes= read(fd[0],mensaje,128);
	
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

	write(fd[1],mensaje,strlen(mensaje));

	close(fd[0]);
	close(fd[1]);

	/*borrar el named pipe*/	
	unlink(argv[1]);
	unlink(argv[2]);

	exit(0);
}
