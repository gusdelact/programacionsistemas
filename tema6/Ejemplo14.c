#include "Ejemplo11.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*consturir todos los mecanismos de concurrencia para el problema
del productor/consumidor*/

main() {

	struct semaforo mutex;
	struct semaforo full;
	struct semaforo empty;
	int sz= (int)('z'-'a');
	int shid;

	mutex.key=123456;
	mutex.valorinicial=1;
	creaSemaforo(&mutex);

	if ( mutex.semId < 0) {
		printf("Error al crear el mutex\n");
		exit(1);
	}

	empty.key=333;
	empty.valorinicial=(int) ('z'-'a');
	creaSemaforo(&empty);

	if ( empty.semId < 0) {
		printf("Error al crear el semaforo empty\n");
		exit(1);
	}


	full.key=444;
	full.valorinicial=0;
	creaSemaforo(&full);

	if ( full.semId < 0) {
		printf("Error al crear el semaforo full\n");
		exit(1);
	}

        /*crear el segmento de memoria compartida*/
        shid= shmget(123456L,sz,IPC_CREAT | 0666);

        if (shid < 0) {
                perror("Error al crear el segmento de memoria compartida");
                exit(3);
        }

        printf("Segmento %d con tamanno %d\n",shid,sz);



}
