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


	/*obtener el segmento de memoria compartida*/
	shid= shmget(123456L,sz, 0); 

	if (shid < 0) {
		perror("Error al obtener el segmento de memoria compartida");
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
			if (buffer[i]!=0) {
				printf(" %c",buffer[i]);
			} else {
			/*si en esta celda aun no se produce nada*/
				printf("Error en lectura de celda %d",i);
				/*consumo no valido*/
				break;
			}
			/*remover*/
			buffer[i]=0;
			i++;
		}
		printf("\n");
	}

	exit(0);
}
