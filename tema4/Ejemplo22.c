/* Ejemplo22 */
#include <fcntl.h>

main() {

	int fd,nbytes;
	char buf[128];

	fd= open("/tmp",O_RDONLY);

	if (fd < 0) {

		perror("No se puede abrir el directorio /tmp");
		exit(1);
	}

	while ( ( nbytes= read(fd,buf,128) ) > 0)	{

		printf("Leyendo %d \n",nbytes);
		write(1,buf,nbytes);
	}

	if (nbytes < 0) {
		perror("Error al leer el directorio"); 
		exit(1);
	}
	exit(0);
}
