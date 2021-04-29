
/*Ejemplo 1
 * Imprimir el identificador de proceso de este programa y el
 * identificador de su proceso padre
 */

#include <unistd.h>
#include <stdio.h>

main(){

	printf("\tPID\tPPID\n");
        /*Se obtiene el identificador del procesos y el de su padre
         *utilizando las llamadas getpid y getppid
         */
	printf("\t%d\t%d\n",getpid(),getppid());
	
}

