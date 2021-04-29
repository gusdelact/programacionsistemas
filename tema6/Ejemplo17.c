#include <sys/msg.h>


main() { 


	int qid;

	/*invocar la llamada mssget, para un cola con llave 123456
	y se crea la cola con permisos de lectura y escritura para
	propietario, grupo y otros usuarios*/
	qid= msgget(123456,IPC_CREAT|0666);

	if (qid < 0) {
		perror("Error al crear la cola de mensajes");
		exit(1);
	}

	printf("Cola creada\n");

	exit(0);


}
