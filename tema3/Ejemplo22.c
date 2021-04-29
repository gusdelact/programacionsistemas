/*Ejemplo22*/

main(int argc,char *argv[]) {


	if (argc > 1) {
		int pid= fork();

		if (pid < 0)
			perror("Error en fork");

		else if (pid==0) { /*El hijo manda a ejecutar el comando*/
			int rtn;
			rtn=execvp(argv[1],&argv[1]);
			printf("este mensaje no sucede ante correcta ejecucion");

			if (rtn<0)
			 	perror("Error en ejecucion");
			exit(1);
		}else
			exit(0);
	}
}

