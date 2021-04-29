#include <sys/msg.h>

struct mensaje {
	long mtype;
	char buffer[25]; 
}

main() { 


	int qid;
	struct mensaje mensaje1={1,"Hola mundo\n"};
	struct mensaje mensaje2={2,"aDIOS mUNDO\n"};
	struct mensaje respuesta;
	int nbytes;

	/*invocar la llamada mssget, para un cola con llave 123456
	y se crea la cola con permisos de lectura y escritura para
	propietario, grupo y otros usuarios*/
	qid= msgget(123456,0);

	if (qid < 0) {
		perror("Error al conectarse a la cola de mensajes");
		exit(1);
	}


	printf("Enviando  mensaje1 ...\n");
	/*enviar mensaje sin esperar que el destinatario lo reciba*/
	if (msgsnd(qid, &mensaje1,strlen(mensaje1.buffer),0) < 0) {
		perror("Mensaje enviado\n");
		exit(2);
	}

	nbytes=msgrcv(qid, &respuesta,25,3,0);
	respuesta.buffer[nbytes]=0;

	if (nbytes < 0) {
		perror("error al leer respuesta");
		exit(3);
	}

	printf("Respuesta de %d bytes es %s\n",nbytes,respuesta.buffer);

	printf("Enviando  mensaje2 ...\n");
	/*enviar mensaje sin esperar que el destinatario lo reciba*/
	if (msgsnd(qid, &mensaje2,strlen(mensaje2.buffer),0) < 0) {
		perror("Mensaje enviado\n");
		exit(2);
	}


	nbytes=msgrcv(qid, &respuesta,25,3,0);
	respuesta.buffer[nbytes]=0;

	if (nbytes < 0) {

		perror("error al leer respuesta");
		exit(3);
	}

	printf("Respuesta de %d bytes es %s\n",nbytes,respuesta.buffer);
	exit(0);


}
