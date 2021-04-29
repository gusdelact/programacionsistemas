#include <unistd.h>

/*Procesamiento utilizando varios pipes encadenados*/

main() {

int pids[2];
int pipefd1[2];
int pipefd2[2];
int rtn,i;

	/*1. El proceso padre crea dos pipes.
	 */	
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

	for (i=0;i<3;i++) {

		rtn=fork();		
		if (rtn<0) {
			perror("no puedo generar un proceso hijo");
			exit(2);
		}
		if (rtn==0) {

			if (i==0) {

				/*este proceso cierra 
				extremo de lectura del pipe1*/
				close(pipefd1[0]);
				/*se cierran los extremos del otro pipe*/
				close(pipefd2[0]);
				close(pipefd2[1]);

				/*y escribe al extremo de escritura
				del pipe1*/

				rtn= write(pipefd1[1],&i,sizeof(i));
	
				if (rtn< 0) {
					perror("Error al escribir al pipe1");
					exit(1);
				}

				printf("Proceso %d escribe %d bytes con valor %d\n",
					getpid(),rtn,i);
				/*cierra extremo de escritura*/
				close(pipefd1[1]);
				exit(0);
			} else if ( i==1) {
				int j;
				/*este proceso cierra extremo de escritura
				del pipe1*/
				close(pipefd1[1]);
				/*cierra el extremo de lectura del pipe2*/
				close(pipefd2[0]);

				/*y lee el mensaje del cliente*/
				rtn=
				read(pipefd1[0], &j,sizeof(j));

				if (rtn< 0) {
					perror("Error al leer el pipe1");
					exit(1);
				}
				printf("Proceso %d lee %d bytes con valor %d\n",
                                        getpid(),rtn,j);

				/*se incrementa en 2 el valor que se recibe*/
				j=j+2;
			
				/*se escribe al pipe2 el valor de j*/
				rtn= write(pipefd2[1],&j,sizeof(j));
	
				if (rtn< 0) {
					perror("Error al escribir al pipe2");
					exit(1);
				}
				printf("Proceso %d escribe %d bytes con valor %d\n",
					getpid(),rtn,j);

				close(pipefd1[0]);
				close(pipefd2[1]);
				exit(0);
	
			} else if (i==2) {
				int k;

				/*este proceso cierra los extremos
				del pipe1*/

				close(pipefd1[0]);
				close(pipefd1[1]);
			
				/*y el extremo de escritura del pipe2*/
				close(pipefd2[1]);
				/*y lee el mensaje del cliente*/
				rtn=
				read(pipefd2[0], &k,sizeof(k));

				if (rtn< 0) {
					perror("Error al leer el pipe1");
					exit(1);
				}
				k+=2;
				printf("Proceso %d lee %d bytes con valor %d\n",
                                        getpid(),rtn,k);
			
				/*cierra los extremos*/
				close(pipefd2[1]);	
				exit(0);
			}
		} else {
			printf("Proceso %d genero hijo %d\n",getpid(),rtn);
		}
	}

	/*Esperar a los hijos*/
	for (i=0;i<=2;i++) {
		printf("Esperando a mis hijos...\n");
		wait((int *)0);
	}

	exit(0);	
}
