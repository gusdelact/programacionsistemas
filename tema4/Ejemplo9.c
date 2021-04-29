/*Ejemplo9 Borrar un archivo*/
#include <unistd.h>

main(int argc, char *argv[]) {

	int rtn;

	if (argc==1) {
		printf("Ejemplo9: Ejemplo9 archivo_a_borrar\n");
		exit(1);
	}

	rtn=unlink(argv[1]);

	if (rtn < 0) {
		perror("Error al tratar de borrar el archivo");
	}

}

