#include <sys/msg.h>


main() { 


	int qid;

	/*invocar la llamada mssget, para un cola con llave 123456
	y se crea la cola con permisos de lectura y escritura para
	propietario, grupo y otros usuarios*/
	qid= msgget(123456,0);

	if (qid < 0) {
		perror("Error al crear la cola de mensajes");
		exit(1);
	}

	/* destruir la cola con la llamada msgctl, el segundo parametro,
	con valor IPC_RMID indica esta instruccion
	*/
	if ( msgctl(qid,IPC_RMID,0) < 0) {
		perror("Error al remover la cola de mensajes");
		exit(2);
	}


	printf("Cola destruida\n");

	exit(0);


}
