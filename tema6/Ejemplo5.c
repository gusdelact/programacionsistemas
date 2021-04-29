#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "Ejemplo4.h"

#define CONTADOR "contador"


main(int argc, char * argv[]) {


	int fd; /*descriptor del archivo a leer/escribir*/
	int pid; 
	int contador=0; /*variable contador*/
	int i;
	char sContador[4]; /*contenido del 
				archivo de maximo tres posiciones*/
	char mensaje[256]; /*buffer de mensaje para depurar*/
	int nProcs; /*numero de procesos a arrancar*/
	struct semBinario sem;

	if (argc <=1 ) {
		printf("Ejemplo5 nProcesos\n");
		exit(1);
	}	

	nProcs=atoi(argv[1])-1;

	/*abrir el archivo para lectura y escritura*/

	fd= open(CONTADOR, O_RDWR);

	if (fd < 0) {
		perror("Error al abir el archivo");
		exit(1);
	}

	/*el proceso padre crea el semaforo*/
	sem.key=123456L;
	creaSemaforoBinario(&sem);

	if (sem.semId < 0 ) {
		perror("Error al crear el semaforo");
		exit(2);
	}

	/*crear nProcs */
	for (i=0;i<nProcs;i++) {
		pid=fork();

		if (pid < 0) {
			perror("Error al crear al hijo");
			exit(2);
		} 
	}

	/*padre e hijo ejecutan el mismo codigo*/

	while ( contador < 99){
		int nbytes;	

		sprintf(mensaje,"Proceso %d efectuando down\n",getpid());
		write(1,mensaje,strlen(mensaje));

		/*bajar el semaforo*/
		if ( down(&sem) )
			perror("Error al bajar semaforo");	

		sprintf(mensaje,"Proceso %d concluyendo down\n",getpid());
		write(1,mensaje,strlen(mensaje));

		/*poner el descriptor al inicio del archivo*/	
		if ( lseek(fd,0,SEEK_SET) ){
			perror("Error en lseek");
		}
		

		/*leer el archivo*/
		nbytes= read(fd,sContador,sizeof(sContador));	

		if (nbytes < 0)  {
			perror("Error al leer el archivo");
			exit(2);
		}

		/*quitar \n y poner un nulo*/
		sContador[nbytes-1]=0;

		/*se escribe a salida estandar los mensajes*/
		sprintf(mensaje,"PID %d lee contador %s %d bytes\n",getpid(),sContador,nbytes);	
		write(1,mensaje,strlen(mensaje));

		/*convertir el contador a entero*/
		contador=atoi(sContador);

		/*incrementar contador*/
		contador++;

		/*se escribe a salida estandar los mensajes*/
		sprintf(mensaje,"PID %d poner contador a valor %d\n",getpid(), contador);
		write(1,mensaje,strlen(mensaje));	

		/*escribir el resultado al inicio del archivo*/
		if ( lseek(fd,0,SEEK_SET) ){
			perror("Error en lseek");
		}

		sprintf(sContador,"%d\n",contador);

		write(fd,sContador,strlen(sContador));	

		sprintf(mensaje,"Proceso %d efectuando up\n",getpid());
		write(1,mensaje,strlen(mensaje));

		/*subir al semaforo*/	
		if (up(&sem) < 0)
			perror("Error al subir el semaforo");
		sprintf(mensaje,"Proceso %d concluyendo up\n",getpid());
		write(1,mensaje,strlen(mensaje));
	}

	/*cerrar el archivo*/
	close(fd);

}
