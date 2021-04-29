#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>

/*Ejemplo9, realiza una lectura de un pipe, pero sin que se bloquee en
un open, sino que utiliza escrutinio o polling con la llamada select
*/

main(int argc, char * argv[]) {

	int rtn;
	int fd;
	int nbytes,j;
	char mensaje[128];
	fd_set readset; /*esta variable se utiliza para la llamada select*/

	if (argc <= 1) {
		printf("Ejemplo9 rutaFIFO \n");
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

	printf("PID %d Abriendo el named PIPE\n", getpid());
	/*obtener el descriptor de archivo de lectura y no bloquerase*/
	fd= open(argv[1],O_RDONLY|O_NONBLOCK);	

	if (fd < 0) {
		perror("Error al abrir extremo de lectura del pipe");
		exit(2);
	}

	/*Realizar escrutinio o polling*/
	printf("PID %d Esperando el mensaje con un select...\n", getpid());
	FD_ZERO(&readset);
	FD_SET(fd,&readset);
	rtn=select(fd+1,&readset,0,0,0);

	if (rtn< 0) {
		perror("Error en escrutinio");
		exit(2);
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
