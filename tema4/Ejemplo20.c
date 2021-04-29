#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Ejemplo20 Uso de chdir y fchdir */

main() {
	int rtn,fd;

	/*cambiarse al directorio /tmp*/

	rtn= chdir("/tmp");

	if (rtn < 0) {
		perror("Error al cambiarse al directorio /tmp");
		exit(1);
	}	

	/*Crear un subdirectorio dentro de /tmp*/

	rtn= mkdir("980432",0700);

	if (rtn < 0) { 
                perror("Error al crear al directorio /tmp/mio");
                exit(2);
        }   

	/*Cambiarse al directorio /tmp/mio, utilizando open y fchdir*/

	fd=open("980432",O_RDONLY);

	if (fd < 0) {
		perror("Error al abrir el directorio /tmp/mio");	
		exit(3);
	}

	rtn=fchdir(fd);	
	if (rtn < 0) { 
                perror("Error al crear al cambiarse al directorio /tmp/mio");
                exit(4);
        }   

	fd= creat("archivo1",0644);

	if (fd < 0) {
		perror("Error al crear el archivo /tmp/mio/archivo1");	
		exit(5);
	}

	
	/*concluir con un listado recursivo de /tmp/mio*/

	rtn=execl("/bin/ls","/bin/ls","-lR",(char *)0);

	if (rtn < 0) {
		perror("Error al ejecutar ls");
		exit(6);
	}

	exit(0);	
}
