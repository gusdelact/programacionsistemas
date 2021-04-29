/*Ejemplo5  Abrir varios archivos, sin cerrar*/

#define O_RDONLY 0
main(int argc, char * argv[]) {

	int fd;

	fd= open("/etc/hosts", O_RDONLY);
	printf("El descriptor del archivo es %d\n", fd);
	close(fd);

	fd= open("/etc/passwd", O_RDONLY);
	printf("El descriptor del archivo es %d\n", fd);
	close(fd);

	fd= open("/etc/services", O_RDONLY);
	printf("El descriptor del archivo es %d\n", fd);
	close(fd);

}

