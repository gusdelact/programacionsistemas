#include <sys/msg.h>

struct mensaje {
	long mtype;
	char buffer[25]; 
}

main() { 


	int qid;
	struct mensaje mensaje;
	int i,nbytes;

	/*invocar la llamada mssget, para un cola con llave 123456
	y se crea la cola con permisos de lectura y escritura para
	propietario, grupo y otros usuarios*/
	qid= msgget(123456,IPC_CREAT|0666);

	if (qid < 0) {
		perror("Error al crear la cola de mensajes");
		exit(1);
	}

	printf("Cola creada\n");

	
	while (1) {
		printf("Esperando recibir mensaje ...\n");

		/*espera recibir un mensaje de  tipo (1 o 2) y 
		con longiut de 25 bytes*/
		nbytes=msgrcv(qid, &mensaje,25,-2,0);

		if (nbytes < 0) {
			perror("Error al recibir el mensaje");
			exit(2);
		}

		mensaje.buffer[nbytes]=0;
		printf("mensaje de %d bytes de tipo %d con valor %s\n",
			nbytes,mensaje.mtype ,mensaje.buffer);


		if (mensaje.mtype == 1) { /*cambiar a mayusculas*/
			for (i=0;i< strlen(mensaje.buffer);i++) {
				mensaje.buffer[i]=toupper(mensaje.buffer[i]);
			}

		} else if (mensaje.mtype==2) { /*cambiar a minusculas*/
			for (i=0;i< strlen(mensaje.buffer);i++) {
				mensaje.buffer[i]=tolower(mensaje.buffer[i]);
			}
		} 

		/*si no coincide con ningun tipo, envia el mensaje en
		su formato original*/

		/*enviar mensaje de respuesta*/
		mensaje.mtype=3;
		mensaje.buffer[nbytes]=0;
		if (msgsnd(qid,&mensaje,strlen(mensaje.buffer),0) < 0 ) {
			perror("Error al enviar mensaje de respuesta");
			exit(3);
		}

	}    
	exit(0);


}
