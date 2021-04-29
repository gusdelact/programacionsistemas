#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "Ejemplo4.h"
#include "Ejemplo11.h"

main() {

	int shid;
	char * buffer;
	char ch;
	int i;
	int sz= (int)('z'-'a');
        struct semaforo mutex;
        struct semaforo empty;
        struct semaforo full;

	/*conectar al segmento de memoria compartida*/
	shid= shmget(123456L,sz, 0); 

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

	mutex.key=123456;
	abreSemaforo(&mutex);

	if (mutex.semId < 0) {
		perror("Error al abrir mutex");
		exit(5);
	}



	empty.key=333;
	abreSemaforo(&empty);

	if (empty.semId < 0) {
		perror("Error al abrir empty");
		exit(6);
	}

	full.key=444;
	abreSemaforo(&full);

	if (full.semId < 0) {
		perror("Error al abrir full");
		exit(7);
	}

	while (1) {

		i=0;
		for (ch='a';ch<='z';ch++) {
			printf("Escribiendo %c en celda %d\n",ch,i);

			if ( P(&empty) < 0 ) {
				perror("Error en empty.P");
				exit(8);
			}


			if ( P(&mutex) < 0 ) {
				perror("Error en mutex.P");
				exit(9);
			}

			buffer[i]=ch;
			i++;

			if ( V(&mutex) < 0 ) {
				perror("Error en mutex.V");
				exit(10);
			}


			if ( V(&full) < 0 ) {
				perror("Error en full.V");
				exit(11);
			}

		}
	}

	exit(0);
}
