#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define SEMKEY 123456L


main() {

	int semid;

	/*crear un conjunto de semaforo de tamanno 1, 
	con permiso de lectura y asignacion para cualquier usuario
	*/
	semid=semget(SEMKEY, 1, IPC_CREAT | 0666);

	/*checar si existe algun error*/
	if (semid < 0) {
		perror("Error al crear el semaforo");
		exit(1);
	}
	printf("Semaforo creado\n");

	exit(0);
}

