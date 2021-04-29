#define O_RDONLY 0
#define O_WRONLY 1
main(int argc, char * argv[]) {

	char * nombrearchivo;
	int fd;

	if (argc==1) {
		printf("Ejemplo1: proporcionar un nombre de archivo");
		exit(1);
	} else {
		nombrearchivo=argv[1];
	}

	fd= open(nombrearchivo,O_WRONLY);

	if (fd < 0) {
		perror("Checar la ruta o permisos del archivo");
		exit(2);
	} else {
		printf("El descriptor del archivo es %d", fd);
		exit(0);
	}	
}

