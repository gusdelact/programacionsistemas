#include <sys/types.h>
#include <dirent.h>


main(int argc,char *argv[]) {

	DIR * directorio;
	struct dirent *direntp;
	int rtn;

	if (argc ==1) {

		printf("Ejemplo23: Ejemplo23 directorio\n");
		exit(1);
	}

	directorio=opendir(argv[1]);

	if (directorio == (DIR *) 0) {
		perror("Error al abrir el directorio");
		exit(2);
	}

	while ( ( direntp=readdir(directorio) ) != (struct dirent *) 0 ) {
		printf("Archivo %s \n",direntp->d_name);
	}

	rtn=closedir(directorio);

	if (rtn< 0) {
		perror("Error al cerrar el directorio");
		exit(3);
	}

	exit(0);

}
