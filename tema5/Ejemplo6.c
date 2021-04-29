#include <sys/stat.h>

/*Ejemplo6, crea un named PIPE */

main(int argc, char * argv[]) {

	int rtn;

	if (argc <= 1) {
		printf("Ejemplo6 rutaFIFO \n");
		exit(1);
	}

	/*Indica al kernel que debe crear un archivo de tipo PIPE
	  El segundo parametro es una mascar de bits.
	  Se efectua una operacion OR de bits para indicar que
	  es un FIFO y que los permisos son de lectura/escritura
	  propietario, lectura para grupo y lectura para otros
	*/
	rtn= mknod(argv[1],S_IFIFO | 0644, 0);

	if (rtn < 0) {

		perror("Error al crear el named pipe");
		exit(2);
	}	

	exit(0);
}
