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
	exit(0);
}
