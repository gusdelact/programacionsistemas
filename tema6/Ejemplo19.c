#include <sys/msg.h>

struct mensaje {
	long mtype;
	char buffer[20]; 
}

main() { 


	int qid;
	struct mensaje mensaje;
	int nbytes;

	/*invocar la llamada mssget, para un cola con llave 123456
	y se crea la cola con permisos de lectura y escritura para
	propietario, grupo y otros usuarios*/
	qid= msgget(123456,IPC_CREAT|0666);

	if (qid < 0) {
		perror("Error al crear la cola de mensajes");
		exit(1);
	}

	printf("Cola creada\n");

	printf("Esperando recibir mensaje ...\n");

	/*espera recibir un mensaje de tipo 1 y con longiut de 25 bytes*/
	nbytes=msgrcv(qid, &mensaje,25,1,0);

	if (nbytes < 0) {
		perror("Error al recibir el mensaje");
		exit(2);
	}
	printf("mensaje de %d bytes con valor %s\n",nbytes,mensaje.buffer);
	exit(0);


}
