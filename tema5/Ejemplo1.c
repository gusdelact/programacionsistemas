/*Ejemplo1, Crear un pipe con la entrada y salida estandar del proceso
	actual.
*/ 

#include <unistd.h>

main(){

	int fildes[2]; /*arreglo de descriptores de archivos*/
	int rtn;
	char mensaje[]="hola pipe\n";
	char buffer[128];
	int nbytes;

	/*Crear el pipe*/

	rtn=pipe(fildes);

	if (rtn < 0) {
		perror("No se puede crear el pipe");
		exit(1);
	}

	/*Checar los descriptores de archivos del pipe*/

	printf("Pipe read %d \n Pipe write %d\n",fildes[0],fildes[1]);

	/*Escribir algo en el pipe*/

	if ( write(fildes[1],mensaje,strlen(mensaje) ) != strlen(mensaje) ) {
		perror("Error al escribir al pipe");
		exit(2);
	}

	if ( 
		(nbytes=read(fildes[0],buffer,128)) <= 0
	) {
		perror("Error al leer el pipe\n");
		exit(3);
	}

	write(1,buffer,nbytes);

	exit(0);	
}
