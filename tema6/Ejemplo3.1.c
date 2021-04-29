#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define SEMKEY 123456L

/* se declara esta union para la llamada semctl*/
union semun {
       int val;
       struct semid_ds *buf;
       ushort *array;
 };

main() {

	int semid;
	union semun semctl_arg;

	/*crear un conjunto de semaforo de tamanno 1, 
	con permiso de lectura y asignacion para cualquier usuario
	*/
	semid=semget(SEMKEY, 1,IPC_CREAT|0666);

	/*checar si existe algun error*/
	if (semid < 0) {
		perror("Error al obtener  el conjunto de semaforo");
		exit(1);
	}


	/*leer el valor con el comando GETVAL*/	
	semctl_arg.val=semctl(semid,0,GETVAL) ;
	if (semctl_arg.val < 0) {
		perror("Error al obtener un valor");
		exit(1);
	}

	printf("Valor actual del semaforo %d\n",semctl_arg.val);

	/*dar un valor de uno al semaforo*/
	semctl_arg.val= 1;
	if (semctl(semid,0,SETVAL,semctl_arg) < 0) {
		perror("Error al asignar un valor");
		exit(1);
	}

	/*leer el valor con el comando GETVAL*/	
	semctl_arg.val= 0;
	semctl_arg.val=semctl(semid,0,GETVAL) ;
	if (semctl_arg.val < 0) {
		perror("Error al obtener un valor");
		exit(1);
	}
	printf("Valor actual del semaforo %d\n",semctl_arg.val);
	
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

