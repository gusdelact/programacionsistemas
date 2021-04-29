/*Ejemplo 20*/
#define MAXPROC 128
int tablaprocesos[MAXPROC];
int contador=0;

void finprocesohijo(void) {

	printf("El PID %d con PPID %d ha muerto!!\n",getpid(),getppid());

}

void finprocesopadre(void) {
	int i;
	for (i=0;i<contador;i++) {
		printf("Destruyendo a %d \n",tablaprocesos[i]);
		/*destruir con valor 9*/
		kill(tablaprocesos[i],9);
	}

	printf("Fin del padre\n");
	
}

main(int argc,char *argv[]) {
	int pid,i;
	if (argc==1)
		contador=1;
	else {
		contador=atoi(argv[1]);
		if (contador>MAXPROC)
			contador=MAXPROC;
	}

	atexit(finprocesopadre);

	for ( i=0;i<contador;i++) {

		pid=fork();
		if (pid==0) {
			atexit(finprocesohijo);
			printf("Proceso hijo %d\n",getpid());
		
			/*Mandar a ejecutar el programa sleep*/	
			execl("/bin/sleep","sleep","3000",(char *)0);
			exit(0);
		} else
			/*Insertar en la tabla de procesos*/
			tablaprocesos[i]=pid;
	}

	/*Llamar a exit del padre*/
	exit(0);
		
}


