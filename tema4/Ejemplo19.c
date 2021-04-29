#include <sys/types.h>
#include <sys/stat.h>

main() {

	/*Crear un directorio con permisos de lectura, escritura y
	ejecucion para el propietario*/
	int rtn,fd;

	rtn=mkdir("dir1",0700);

	if (rtn < 0) {
		perror("Error al crear dir1");
		exit(1);
	}

	/*Crear un directorio con permisos de lectura, escritura 
	 para el propietario*/
	rtn=mkdir("dir2",0600);

	if (rtn < 0) {
		perror("Error al crear dir2");
		exit(1);
	}	

	/*Ahora crear archivos sobre los directorios*/

	fd= creat("dir1/archivo1",0644);
	if (fd < 0) {
		perror("Error al crear dir1/archivo1");
		exit(1);
	}	

	close(fd);
	rtn=mkdir("dir1/subdir1",0700);

	if (rtn < 0) {
		perror("Error al crear dir1/subdir1");
		exit(1);
	}
	
	fd= creat("dir2/archivo1",0644);
	if (fd < 0) {
		perror("Error al crear dir2/archivo1");
		exit(1);
	}

	exit(0);

}
