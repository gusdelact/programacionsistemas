#include <unistd.h> 
#include <sys/fcntl.h> 

main(int argc, char * argv[]) {

	char * nombrearchivo;
	int fd,fd2;
	int pid;
	char buffer1[]="hola papa\n";
	char buffer2[]="adios hijo\n";

	if (argc==1) {
		printf("Ejemplo1: proporcionar un nombre de archivo\n");
		exit(1);
	} else {
		nombrearchivo=argv[1];
	} /*if*/

	/*crear con permisos de lectura y escritura para todos*/
	fd = creat(nombrearchivo, 0644);

	if (fd < 0) {
		perror("Checar la ruta ,permisos del directorio o el archivo si existe");
		exit(2);
	} else {
		printf("El descriptor del archivo es %d\n", fd);

		/*ahora invocar dup*/

		fd2=dup(fd);

		printf("El duplicado del descriptor del archivo es %d\n", fd2);

		pid=fork();

		if (pid==0) {

			int nbytes;

			close(fd);

			nbytes=write(fd2, buffer1,strlen(buffer1));
	
			printf("Escribiendo %d \n",nbytes);	
			printf("El descriptor %d tiene offset %d\n", fd2,
				lseek(fd2,0,SEEK_CUR));
			close(fd2);
			exit(0);	
		} else {

			int status;

			close(fd2);
			/*esperar al hijo*/
			wait(&status);
			lseek(fd,strlen(buffer1),SEEK_SET);
			write(fd, buffer2,strlen(buffer2));

			printf("El descriptor %d tiene offset %d\n", fd,
				lseek(fd,0,SEEK_CUR));
			close(fd);
			exit(0);
		}
	}	
}

