#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define SEMKEY 123456L


main() {

	int semid;
	int pid;
	int val;
	int i;
	/*definir las operaciones sobre semaforos*/
	struct sembuf semop1[2], semop2;
	char buffer[128];

	/*crear un conjunto de semaforo de tamanno 1, 
	con permiso de lectura y asignacion para cualquier usuario
	*/
	semid=semget(SEMKEY, 1,IPC_CREAT|0666);

	/*checar si existe algun error*/
	if (semid < 0) {
		perror("Error al obtener  el conjunto de semaforo");
		exit(1);
	}

	/*La primera operacion es :
		Leer el semaforo y esperar hasta que sea 0
			E
		Incrementar el valor del semaforo
	*/	
	semop1[0].sem_num=0;
	semop1[0].sem_op=0 ;
	semop1[0].sem_flg=0;
	semop1[1].sem_num=0;
	semop1[1].sem_op=1;
	semop1[1].sem_flg=0;
	
	/*La segunda operacion es decrementar el valor del semaforo
	en una unidad*/
	semop2.sem_num=0;
	semop2.sem_op=-1 ;
	semop2.sem_flg=0;
	
		
	for (i=0;i<2;i++) {
		pid=fork();
		
		if (pid < 0) {
			perror("Error al crear nuevo proceso");
			exit(2);
		}
	}

	/*leer el valor con el comando GETVAL*/	
	val=semctl(semid,0,GETVAL) ;
	if (val < 0) {
		perror("Error al obtener un valor");
		exit(1);
	}
	sprintf(buffer,"PID %d Valor actual del semaforo %d\n",getpid(),val);
	write(1,buffer,strlen(buffer));
	/*efectuar la operacion 1, se queda bloqueda si el proceso
	encuentra un valor del semaforo diferente de 0*/
	sprintf(buffer,"PID  %d aplicando operacion1\n",getpid());
	write(1,buffer,strlen(buffer));
	semop(semid, &semop1[0], 2);

	sprintf(buffer,"PID %d entrando a seccion critica\n",getpid());
	/*leer el valor con el comando GETVAL*/	
	val=semctl(semid,0,GETVAL) ;
	if (val < 0) {
		perror("Error al obtener un valor");
		exit(1);
	}
	sprintf(buffer,"PID %d entrando a seccion critica\n",getpid());
	write(1,buffer,strlen(buffer)); 


	sprintf(buffer,"PID %d Valor actual del semaforo %d\n",getpid(),val);
	write(1,buffer,strlen(buffer));

	sprintf(buffer,"PID %d saliendo de seccion critica\n",getpid());
	write(1,buffer,strlen(buffer));

	/*decrementar el valor del semaforo, despierta a los
	demas procesos*/	
	sprintf(buffer,"PID  %d aplicando operacion2\n",getpid());
	write(1,buffer,strlen(buffer));
	semop(semid, &semop2, 1);

	/*leer el valor con el comando GETVAL*/	
	val=semctl(semid,0,GETVAL) ;
	if (val < 0) {
		perror("Error al obtener un valor");
		exit(1);
	}
	sprintf(buffer,"PID %d Valor actual del semaforo %d\n",getpid(),val);
	write(1,buffer,strlen(buffer));

	
	exit(0);
}

