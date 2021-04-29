/*Ejemplo 4
 * Crear un abanico de procesos 
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/*Recibe desde la linea de comandos cuantos procesos crear en el abanico*/
main(int argc,char *argv[]){

        int chPid;
        int numProcesos,i;

        if (argc==1)
                numProcesos=1;
        else
                numProcesos=atoi(argv[1]);

        for (i=1;i<=numProcesos;i++) {
                /*Crear nuevo proceso*/
                chPid=fork();
                /*Aqui ya se bifurco*/
                if (chPid!=0) { /*este es el papa*/
                        printf("PID %d  papa de %d\n",getpid(),chPid);
                        /*Continuar el ciclo,  y crear un hijo*/
                }else {
                        printf("\tPID\tPPID\n");
                        /*Se obtiene el identificador del procesos
                         * y el de su padre
                        *utilizando las llamadas getpid y getppid
                        */
                        printf("\t%d\t%d\n",getpid(),getppid());
               }/*if*/

        }/*for*/

}

