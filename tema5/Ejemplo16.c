#include <signal.h>

int contador=0;

void cambioHijo(int sig) {

	printf("Cambio un hijo signo %d contador %d\n",sig,contador);
	contador++;
}


main() {

	int i;

	struct sigaction nuevaAccion;
	int rtn;

	/*Llenar la estructura sigaction*/
	nuevaAccion.sa_handler=cambioHijo ; /*la funcion manejadora no existe,
					solo se ignora*/
	sigemptyset(&nuevaAccion.sa_mask); /*no se bloque ninguna sennal*/
	nuevaAccion.sa_flags=0; /*no hay banderas*/

	rtn=sigaction(SIGCHLD,&nuevaAccion,(struct sigaction *)0);
	
	if (rtn < 0) {
		perror("Error al registar manejador de signal");
		exit(1);
	}

	for (i=0;i< 10; i++) {
		int pid;
		pid=fork();
			

		if (pid < 0) {
			perror("Error en fork");
			exit(1);
		} else if (pid == 0) {
			printf("PID %d valor de i=%d\n",getpid(),i);
			exit(0);
		} else {
			printf("Hijo con pid %d creado\n",pid);
		}
		
	}

	printf("Procesando...\n");
	while (1) {
		if (contador>=10)
			break;
	}

	printf("Acabaron todos mis hijos\n");
	exit(0);
}
