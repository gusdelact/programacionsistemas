#include <signal.h>

void division(int signo) {
	printf("Division incorrecta signo %d\n",signo);
	exit(1);
}
main() {

	struct sigaction nuevaAccion;
	int rtn,x;
	char * ptr=0;

	/*Llenar la estructura sigaction*/
	nuevaAccion.sa_handler= division; /*la funcion manejadora no existe,
					solo se ignora*/
	sigemptyset(&nuevaAccion.sa_mask); /*no se bloque ninguna sennal*/
	nuevaAccion.sa_flags=0; /*no hay banderas*/

	/*ante un Ctrl-C no se muere el proceso*/
	rtn=sigaction(SIGFPE,&nuevaAccion,(struct sigaction *)0);
	
	if (rtn < 0) {
		perror("Error al registar manejador de signal");
		exit(1);
	}


	x=1/0;
}
