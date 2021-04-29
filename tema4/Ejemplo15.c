#include <unistd.h> 
#include <sys/fcntl.h> 

main(int argc, char * argv[]) {

	char * nombrearchivo;
	int fd,fd2;

	if (argc==1) {
		printf("Ejemplo1: proporcionar un nombre de archivo\n");
		exit(1);
	} else {
		nombrearchivo=argv[1];
	} /*if*/

	/*crear con permisos de lectura y escritura para todos*/
	fd = open(nombrearchivo, O_RDONLY);

	if (fd < 0) {
		perror("Checar la ruta ,permisos del directorio o el archivo si existe");
		exit(2);
	} else {
		printf("El descriptor del archivo es %d\n", fd);

		/*ahora invocar dup*/

		fd2=dup(fd);

		printf("El duplicado del descriptor del archivo es %d\n", fd2);


		printf("El descriptor %d tiene offset %d\n", fd,
				lseek(fd,0,SEEK_SET));
		printf("El descriptor %d tiene offset %d\n", fd2,
				lseek(fd2,0,SEEK_END));

		
		close(fd);
		close(fd2);
		exit(0);
	}	
}

