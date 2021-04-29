/*Ejemplo 11
 * Muestra el uso de la llamada waitpid con multiples procesos
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

main(int argc, char *argv[]) {

	int pid,nproc,i;

	int status; /*valor que contendra el estado del proceso hijo*/
	int tablaProcesos[128]; /*arreglo con identificadores de procesos*/
	
	if (argc==1)
		nproc=1;
	else {
		nproc=atoi(argv[1]);

		/*guardar solo a 128 PID*/
		if (nproc>128)
			nproc=128;
	}

	/*crear un abanico de procesos*/

	for (i=0; i< nproc;i++) {
		pid=fork(); /*bifurcarse*/

		
		if (pid == 0) {
			int i;
			printf("Soy el hijo \n");
			/*ejecutar un ciclo ocioso*/
			for (i=0;i<10000;i++);
			printf("Concluye el hijo  \n");
			break;		
		} else {
			printf("Tuve un hijo con PID %d",pid);
			tablaProcesos[i]=pid;
			continue;
		}/*if*/

	}/*for*/

	/*este es el proceso padre*/
	if (pid!=0) {
		/*Imprimir toda la tabla de procesos */
		printf("\n******************************************\n");
		for (i=0; i< nproc;i++) {
			printf("%d ",tablaProcesos[i]);
		}/*for*/
		printf("\n******************************************\n");

		/*esperar a cada hijo*/
		for (i=0; i< nproc;i++) {


			int rpid;
			int status;
			rpid=waitpid(tablaProcesos[i],&status,0);

			if (rpid==tablaProcesos[i]) {
				printf("Concluye el hijo con PID %d y estado %d\n",rpid,status);
			} else {
				perror("El hijo tuvo problemas");
			}/*if*/
			tablaProcesos[i]=rpid;


		}/*for*/

 		/*Imprimir toda la tabla de procesos */

		printf("\n******************************************\n");
		for (i=0; i< nproc;i++) {
			printf("%d ",tablaProcesos[i]);
		}/*for*/
		printf("\n******************************************\n");
	}/*if*/
}

