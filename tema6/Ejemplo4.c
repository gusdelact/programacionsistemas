#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "Ejemplo4.h"



void creaSemaforoBinario(struct semBinario * sembin) {
	/*obtiene la llave*/
	int key= sembin->key;
	/*una llave menor o igual a cero no es aceptable*/
	if (key <= 0 ){
		sembin->semId= -1;
		return;
	}
	sembin->semId= semget(sembin->key, 1, IPC_CREAT | 0666);
}

int down(struct semBinario * sembin) {

	struct sembuf opdown[2];

	/* la operacion a realizar es:*/
	/*leer el valor esperando que sea 0, sino bloquerse*/
	opdown[0].sem_num=0;
	opdown[0].sem_op=0;
	opdown[0].sem_flg=0;
	/*E incrementar en una unidad el semaforo*/
	opdown[1].sem_num=0;
	opdown[1].sem_op=1;
	opdown[1].sem_flg=0;

	return semop(sembin->semId, &opdown[0],2);
}

int up(struct semBinario * sembin) {
	struct sembuf opup;

	/*la operacion a realizar es:
	decrementar en una unidad el semaforo si y solo si 
	tiene un valor de 1
	*/
	opup.sem_num=0;
	opup.sem_op=-1;
	opup.sem_flg=0;

	return semop(sembin->semId, &opup,1);


}
