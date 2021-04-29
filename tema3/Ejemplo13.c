/*Ejemplo 13, uso de la familia de llamadas exec.
 * se realiza un ls -l 
 */
#include <unistd.h>
#include <stdio.h>

main(int argc, char *argv[], char *envp[]) {

	char comandoconruta[]="/bin/ls";
	char comandosinruta[]="ls";
	char *argumentos[]={"/bin/ls","-l",(char *)0};
	int pid;
	int rtn; /*valor de retorno*/

	pid=fork();
	/*se debe bifurcar, ya que la llamada exec no es reentrante*/

	if (pid==0) {
		printf("Ejecutando ls -l con execl\n");
		rtn=execl(comandoconruta,"/bin/ls","-l",(char *)0);

		if (rtn==-1)
			perror("Error en execl");
	}
	/*Esperar al hijo*/
	waitpid(pid,(int *)0,0);

	pid=fork(); 
	/*se debe bifurcar, ya que la llamada exec no es reentrante*/

	if (pid==0) {
		printf("Ejecutando ls -l con execv\n");
		rtn=execv(comandoconruta,argumentos);

		if (rtn==-1)
			perror("Error en execv");
	}
	/*Esperar al hijo*/
	waitpid(pid,(int *)0,0);

	pid=fork(); 
	/*se debe bifurcar, ya que la llamada exec no es reentrante*/

	if (pid==0) {
		printf("Ejecutando ls -l con execle\n");
		rtn=execle(comandoconruta,"/bin/ls","-l",(char *)0,envp);

		if (rtn==-1)
			perror("Error en execle");
	}
	/*Esperar al hijo*/
	waitpid(pid,(int *)0,0);

        pid=fork();
        /*se debe bifurcar, ya que la llamada exec no es reentrante*/

        if (pid==0) {
                printf("Ejecutando ls -l con execve\n");
                rtn=execve(comandoconruta,argumentos,envp);

                if (rtn==-1)
                        perror("Error en execve");
        }
        /*Esperar al hijo*/
        waitpid(pid,(int *)0,0);


        pid=fork();
        /*se debe bifurcar, ya que la llamada exec no es reentrante*/

        if (pid==0) {
                printf("Ejecutando ls -l con execlp\n");
                rtn=execlp(comandosinruta,"ls","-l",(char *)0);

                if (rtn==-1)
                        perror("Error en execlp");
        }
        /*Esperar al hijo*/
        waitpid(pid,(int *)0,0);


         pid=fork();
        /*se debe bifurcar, ya que la llamada exec no es reentrante*/

        if (pid==0) {
                printf("Ejecutando ls -l con execvp\n");
                rtn=execvp(comandosinruta,argumentos);

                if (rtn==-1)
                        perror("Error en execvp");
        }
        /*Esperar al hijo*/
        waitpid(pid,(int *)0,0);


	printf("Fin de pruebas con familia exec\n");
	

}

