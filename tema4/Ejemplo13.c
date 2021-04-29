/*Ejemplo13 Calcula tamaño de un archivo*/
#include <unistd.h>
#include <sys/fcntl.h>

main(int argc, char *argv[]) {

	int offset,fd;

	if (argc==1) {
		printf("Ejemplo13: Ejemplo13 archivo \n");
		exit(1);
	}

	fd= open(argv[1],O_RDONLY);


	if (fd<0) {
		perror("Error al abrir el archivo");
	}

	/*Posicionarse offset bytes, con respecto al origen*/

	offset=	lseek(fd,0,SEEK_END);

	if (offset <0 ){
		perror("Error al posicionar en fin de archivo");
	}

	printf("Tamanno es %d\n",offset);

	close(fd);
	exit(0);

}

