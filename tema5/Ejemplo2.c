#include <unistd.h>

main() {

	int pids[2];
	int pipefd[2];
	int rtn,i;

	/*Crear el pipe*/	
	rtn= pipe(pipefd);

	if (rtn< 0) {
		perror("No se puede generar el pipe");
		exit(1);
	}

	/*generar procesos hijos*/
	for (i=0;i<=1;i++) {

		printf("Proceso %d Bifurcando..\n",getpid());
		rtn=fork();

		if (rtn<0) {
			perror("no puedo generar un proceso hijo");
			exit(2);
		}
		if (rtn==0) {

			if (i==0) { /*proceso que genera informacion*/

				/*Este proceso se conoce como el proceso
				cliente */

				char buffer[]="hola mundo\n";
				char respuesta[128];
				int nbytes;

				printf("Proceso %d genera mensaje %s\n",
				getpid(),buffer);

				/*escribir mensaje al pipe, en el descriptor
				  de escritura
 				*/
				close(pipefd[0]);
				write(pipefd[1],buffer,strlen(buffer));

				close(pipefd[1]);

				exit(0);
			} else { /*Proceso servidor */
				char mensaje[128];
				int nbytes;
				int j;

				printf("Proceso %d esperando mensaje\n",
				getpid());
			
				/* Leer un mensaje en el pipe, en el
				   descriptor de lectura
				*/	
				close(pipefd[1]);
				
				nbytes=
				read(pipefd[0],mensaje,128);

				/*Poner caracter nulo al final*/
				mensaje[nbytes]=0;
				printf("proceso %d procesando mensaje %s de %d bytes\n",
				getpid(),mensaje,nbytes);

				/*Poner el mensaje a mayusculas*/
				for(j=0;j<strlen(mensaje);j++) {
					mensaje[j]=toupper(mensaje[j]);
				}

				printf("proceso %d convierte mensaje %s\n",
				getpid(),mensaje);

				close(pipefd[0]);
				exit(0);

			}
		} else {
			pids[i]=rtn;
		}
	}

	/*Esperar a los hijos*/
	for (i=0;i<=1;i++) {
		printf("Esperando a mis hijos...\n");
		wait((int *)0);
	}

	exit(0);	

}
