#include <signal.h>

void anulaCtlC(int signo) {
	/*esta funcion se llama cuando se recibe un CTRL-C*/
	printf("Recibo señal %d\n",signo);
}

main() {

	struct sigaction nuevaAccion;
	int rtn;

	/*Llenar la estructura sigaction*/
	nuevaAccion.sa_handler= anulaCtlC; /*la funcion manejadora*/
	sigemptyset(&nuevaAccion.sa_mask); /*no se bloque ninguna sennal*/
	nuevaAccion.sa_flags=0; /*no hay banderas*/

	/*ante un CTRL-C no se muere el proceso*/
	rtn=sigaction(SIGINT,&nuevaAccion,(struct sigaction *)0);

	if (rtn < 0) {
		perror("Error al registar manejador de signal");
		exit(1);
	}
	/*se queda procesando para siempre*/
	printf("PID %d Procesando \n",getpid());
	while (1);

	
}

