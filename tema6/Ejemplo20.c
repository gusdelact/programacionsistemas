#include <sys/msg.h>

struct mensaje {
	long mtype;
	char buffer[20]; 
}

main() { 


	int qid;
	struct mensaje mensaje={1,"Hola mundo\n"};

	/*invocar la llamada mssget, para un cola con llave 123456
	y se crea la cola con permisos de lectura y escritura para
	propietario, grupo y otros usuarios*/
	qid= msgget(123456,0);

	if (qid < 0) {
		perror("Error al conectarse a la cola de mensajes");
		exit(1);
	}


	printf("Enviando  mensaje ...\n");
	/*enviar mensaje sin esperar que el destinatario lo reciba*/
	if (msgsnd(qid, &mensaje,strlen(mensaje.buffer),0) < 0) {
		perror("Mensaje enviado\n");
		exit(2);
	}

	exit(0);


}
