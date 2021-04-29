#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

main() {

	int shid;
	char * buffer;
	char ch;
	int i;
	int sz= (int)('z'-'a');


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

	while (1) {

		i=0;
		for (ch='a';ch<='z';ch++) {
			printf("Escribiendo %c en celda %d\n",ch,i);
			buffer[i]=ch;
			i++;
		}
	}

	exit(0);
}
