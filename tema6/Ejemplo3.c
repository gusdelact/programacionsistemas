#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define SEMKEY 123456L


main() {

	int semid;

	/*crear un conjunto de semaforo de tamanno 1, 
	con permiso de lectura y asignacion para cualquier usuario
	*/
	semid=semget(SEMKEY, 1,0);

	/*checar si existe algun error*/
	if (semid < 0) {
		perror("Error al obtener  el conjunto de semaforo");
		exit(1);
	}

	/* se destruye el semaforo, utilizando la llamada semctl,
	el primer parametro es identificador del conjunto de semaforos,
	el segundo indica el numero de semaforo sobre el cual se aplica
	el comando, y el tercer parametro indica que se debe remover
	el conjunto de semaforos
	*/
	if (semctl(semid,0,IPC_RMID) < 0 ) {
		perror("Error al destruir el conjunto de semaforo");
		exit(1);
	}
	printf("Semaforo destruido\n");
	exit(0);
}

