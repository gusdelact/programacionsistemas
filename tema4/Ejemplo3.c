main(int argc, char * argv[]) {

	char * nombrearchivo;
	int fd;

	if (argc==1) {
		printf("Ejemplo1: proporcionar un nombre de archivo\n");
		exit(1);
	} else {
		nombrearchivo=argv[1];
	} /*if*/

	/*crear con permisos de lectura y escritura para todos*/
	fd = creat(nombrearchivo, 0666);

		if (fd < 0) {
		perror("Checar la ruta ,permisos del directorio o el archivo si existe");
		exit(2);
	} else {
		printf("El descriptor del archivo es %d\n", fd);
		exit(0);
	}	
}

