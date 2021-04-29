/* Ejemplo16 Muestra uso de exit*/

main(int argc,char *argv[]) {
	int pid;

	int estadofinal;
	if (argc==1) {
		estadofinal=0;	
	}else 
		estadofinal= atoi(argv[1]);

	pid=fork(); /*bifurcar al proceso*/

	
	if (pid ==0) {
		printf("Hijo con pid %d\n",getpid());
		exit(-estadofinal);
	} else {
		int status,valorRetorno;
		waitpid(pid,&status,0);
		printf("Estado del PID %d es %x\n",pid,status);

		printf("Valor retorno %x\n",(status&0xFF00)>>8);
		printf("Valor retorno %x\n",status&0x00FF);
		valorRetorno=(status&0xFF00)>>8;
		if (valorRetorno==estadofinal)
			printf("El proceso HIJO concluyo en el estado esperado");
		else
			printf("El proceso HIJO no  concluyo en el estado esperado");
			
	}

	
}


