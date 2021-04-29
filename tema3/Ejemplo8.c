/*Ejemplo 8
 * Muestra el uso de la llamada wait
 */
*#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

main() {

	int pid;

	pid=fork(); /*bifurcarse*/

	if (pid == 0) { /*este es el hijo*/
		int i;
		printf("Soy el hijo \n");
		/*ejecutar un ciclo ocioso*/
		for (i=0;i<10000;i++);
		printf("Concluye el hijo  \n");
			
	} else {
		int status; /*valor que contendra el estado del proceso hijo*/
		int rpid;
		printf("Tuve un hijo con PID %d, esperando ...\n",pid);
		rpid=wait(&status);

		/*si el pid de retorno de wait es identico al del hijo*/
		if (rpid==pid)	{
			printf("Concluye el hijo con PID %d y estado %d\n",pid,status);
		} else {
			perror("El hijo tuvo problemas");
		}
		
	}

}
