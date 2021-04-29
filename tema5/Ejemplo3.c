#include <unistd.h>

main() {

	int pids[2];
	int pipefd1[2];
	int pipefd2[2];
	int rtn,i;

	/*Crear el pipe*/	
	rtn= pipe(pipefd1);

	if (rtn< 0) {
		perror("No se puede generar el pipe 1");
		exit(1);
	}

	/*Crear el pipe*/	
	rtn= pipe(pipefd2);

	if (rtn< 0) {
		perror("No se puede generar el pipe 2");
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

				char buffer[]="hola mundo\n";
				char respuesta[128];
				int nbytes;

				printf("Proceso %d genera mensaje %s\n",
				getpid(),buffer);

				/*escribir mensaje al pipe, en el descriptor
				  de escritura
 				*/
				close(pipefd1[0]);
				close(pipefd2[1]);

				write(pipefd1[1],buffer,strlen(buffer));
				printf("Proceso %d esperando respuesta\n",
				getpid()); 

				/*Se queda en una lectura bloqueada sobre
				  el pipe, en el descriptor de lectura
				*/
				nbytes=read(pipefd2[0],respuesta,128);
				/*se pone el caracter nulo en la ultima posicion*/
				respuesta[nbytes]=0;
				printf("proceso %d leyendo respuesta %s de %d bytes\n",
				getpid(),respuesta,nbytes);
				close(pipefd1[1]);
				close(pipefd2[0]);
				exit(0);
			} else { /*Proceso servidor, se arranca primero */
				char mensaje[128];
				int nbytes;
				int j;

				printf("Proceso %d esperando mensaje\n",
				getpid());
			
				/* Leer un mensaje en el pipe, en el
				   descriptor de lectura
				*/	
				close(pipefd1[1]);
				close(pipefd2[0]);
				nbytes=
				read(pipefd1[0],mensaje,128);

				/*Poner caracter nulo al final*/
				mensaje[nbytes]=0;
				printf("proceso %d procesando mensaje %s de %d bytes\n",
				getpid(),mensaje,nbytes);

				/*Poner el mensaje a mayusculas*/
				for(j=0;j<strlen(mensaje);j++) {
					mensaje[j]=toupper(mensaje[j]);
				}

				printf("proceso %d enviando mensaje %s\n",
				getpid(),mensaje);

				/*realizar escritura de la respuesta
				  en el descriptor de escritura del pipe
				*/
				write(pipefd2[1],mensaje,strlen(mensaje));
				close(pipefd1[0]);
				close(pipefd2[1]);
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
