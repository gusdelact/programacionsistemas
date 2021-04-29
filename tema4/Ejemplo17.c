#include <sys/dirent.h>


main() {

	struct dirent dir;
	int nbytes;
	int fd= open("/",O_RDONLY);

	if (fd < 0) 
	{
		perror("No se pudo abrir el directorio");
		exit(1);
	}

	nbytes=read(fd,&dir,sizeof(dir));

	if (nbytes < 0){ 
		perror("No se puede leer el directorio");
		exit(2);
	}

	printf("Numero inodo %d, offset %d, longitud %d, nombre %s\n",
	dir.d_ino,dir.d_off,dir.d_reclen,dir.d_name);

	close(fd);
	exit(0);	
}
