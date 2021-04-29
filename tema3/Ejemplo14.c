
/*Ejemplo14. El usuario puede indicar el programa a ejecutar y
 * por tanto pueden existir errores
 */


main(int argc,char *argv[]) {

	int pid, rtn;


	if (argc>1) {
		/*Bifurcar el programa*/

		printf("Ejecutando %s\n",argv[1]);	
		pid= fork();

		if (pid==0) {
		
			rtn= execv(argv[1],&argv[1]);

			if (rtn==-1) {
				perror("Algo esta mal, intento execvp");
				rtn= execvp(argv[1],&argv[1]);
				if (rtn==-1) {
					perror("Algo esta mal");
				}
				

			}/*if*/
		}/*if*/ 

		waitpid(pid,(int *)0,0);

	}/*if*/
}

