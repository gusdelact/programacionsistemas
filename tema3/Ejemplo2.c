/*Ejemplo 2
 * Crear un proceso hijo y mostrar que es diferente.
 */

#include <unistd.h>
#include <stdio.h>


extern int fork(void);
extern int getpid(void);
extern int getppid(void);
main(){

	int chPid;
	int variable;

	/*Crear un nuevo proceso*/
	chPid=fork(); /*Aqui empieza la división*/

	if (chPid ==0) { /* Este es el hijo*/
		printf("Soy el hijo!! \n");
		for (variable=0;variable<30;variable++);
		printf("El hijo deja variable con valor %d\n",variable);
	} else {
		printf("Soy el padre del proceso %d\n",chPid);
		for (variable=0;variable>-30;variable--);
		printf("El padre deja variable con valor %d\n",variable);

	}

	/*Padre e hijo imprimen identificadores*/
	printf("\tPID\tPPID\n");
        /*Se obtiene el identificador del procesos y el de su padre
       	*utilizando las llamadas getpid y getppid
        */
	printf("\t%d\t%d\n",getpid(),getppid());
	
}

