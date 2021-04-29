#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "Ejemplo11.h"

/* se declara esta union para la llamada semctl*/
union semun {
       int val;
       struct semid_ds *buf;
       ushort *array;
 };


void creaSemaforo(struct semaforo * sem) {
	/*obtiene la llave*/
	int key= sem->key;
	int valorinicial= sem->valorinicial;
	
	/*una llave menor o igual a cero no es aceptable*/
	if (key <= 0 ){
		sem->semId= -1;
		return;
	}

	/*crear el semaforo*/
	sem->semId= semget(sem->key, 1, IPC_CREAT | 0666);
	
	/*indicar el valor del semaforo
		OJO esta rutina solo debe invocarse por SOLO
		un proceso
	*/
	if (sem->semId >= 0) {
		union semun semctl_arg;

		/*dar el valor inicial al semaforo*/
        	semctl_arg.val= sem->valorinicial;
        	if (semctl(sem->semId,0,SETVAL,semctl_arg) < 0) {
               		perror("Error al asignar un valor");
			sem->semId=-2;
               	}
        }
				
}

void abreSemaforo(struct semaforo * sem ) {
	int key= sem->key;

	/*una llave menor o igual a cero no es aceptable*/
	if (key <= 0 ){
		sem->semId= -1;
		return;
	}
	/*abrir el semaforo*/
	sem->semId= semget(sem->key, 1, 0);
}
int P(struct semaforo * sem) {

	struct sembuf opdown[1];

	/* la operacion a realizar es:*/
	/* decrementar en una unidad el semaforo
	con la posibilidad de esperar hasta que el valor del
	semaforo sea igual o mayor al valor absoluto de sem_op*/
	opdown[0].sem_num=0;
	opdown[0].sem_op=-1;
	opdown[0].sem_flg=0;

	return semop(sem->semId, &opdown[0],1);
}

int V(struct semaforo * sem) {
	struct sembuf opup;

	/*la operacion a realizar es:
	incrementar en una unidad el semaforo si y solo si 
	tiene un valor de 1 o superior
	*/
	opup.sem_num=0;
	opup.sem_op=1;
	opup.sem_flg=0;

	return semop(sem->semId, &opup,1);


}
