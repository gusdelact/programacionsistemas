/*Ejemplo17 Muestra la invocación de una función al concluir un proceso*/

void mensajesalida(void) {

	printf("El PID %d con PPID %d ha muerto!!",getpid(),getppid());
}

main() {

	int pid,i;

	atexit(mensajesalida);

	/*crear un abanico de procesos*/
	for (i=0;i<10;i++) {
		pid=fork();
		if (pid==0) {
			printf("Hijo con pid %d\n",getpid());
			exit(i);
		} else {
			int status;
			waitpid(pid,&status,0);
			printf("Valor retorno %x\n",(status&0xFF00)>>8);
		}	

	}

}

