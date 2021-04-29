#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

main() {

	int shid;
	int fd;
	int sz;
	char * buffer;
	int nbytes, totbytes;

	/*abrir el archivo*/
	fd=open("/etc/passwd",O_RDONLY);


	
	if (fd < 0 ) {
		perror("no se puede abrir /etc/passwd");
		exit(1);
	}

	/*Calcular el tamanno del archivo*/
	if ( (sz=lseek(fd,0,SEEK_END)) < 0) {
		perror("Error al calcular tamanno del archivo");
		exit(2);
	}


	/*crear el segmento de memoria compartida*/
	shid= shmget(123456L,sz,IPC_CREAT | 0666); 

	if (shid < 0) {
		perror("Error al crear el segmento de memoria compartida");
		exit(3);
	}

	printf("Segmento %d con tamanno %d\n",shid,sz);

	buffer= (char *)shmat(shid,(void *) 0, 0);

	if (buffer < 0) {
		perror("Error en shmat");
		exit(4);
	}

	/*posicionar el archivo al inicio*/
	lseek(fd,0,SEEK_SET);

	/*cargar el archivo*/

	totbytes=0;	
	while (1) {

		nbytes = read(fd,buffer,sz);

		if (nbytes < 0) {
			perror("Error en read");
			exit(5);
		}

		printf("Leyendo %d bytes \n",nbytes);
		totbytes+=nbytes;
		if ( totbytes >= sz) 
			break;

	}

	printf("Archivo cargado\n");

	if (shmdt(buffer) < 0) {
		perror("Error en shmdt");
		exit(6);
	}

	close(fd);
	exit(0);
}
