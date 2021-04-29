#include <unistd.h>
#include <sys/fcntl.h>

#define BUFSIZ 128
#define MAXFILES 1024
main(int argc, char *argv[]) {

	int fd[MAXFILES] , fddestino;
	int narchivos;
	int i;
	char buffer[BUFSIZ]; /*buffer de lectura y escritura*/
	int nbytes; /*contador de bytes leidos*/

	
	if (argc < 3) { /*Para ejecutar este programa se deben pasar por lo
			menos dos argumentos de la linea de comando*/
		printf("Ejemplo7: Ejemplo7  archivo_origen1 archivo_origen2 ... archivo_destino\n");
		exit(1);
	} else {


		narchivos=  argc-2;

		for (i=0; i< narchivos;i++) {
			fd[i]=open(argv[i+1],O_RDONLY);
			if (fd[i] < 0) {
				perror("Error al abrir un archivo");
				exit(2);
			} /*if*/
			printf("Abriendo archivo %s con descriptor %d\n",argv[i+1],fd[i]);
		} /*for*/

		/*Crear el archivo*/
		fddestino=creat(argv[argc-1],0644);
		
		if (fddestino < 0) {     
                	perror("Error al abrir el archivo destino");
                	exit(2);
                } /*if*/

	} /*if*/

	for (i=0;i<narchivos;i++) {

		int nbytes;
		/*Leer archivo por archivo*/

		while (  (nbytes = read(fd[i],buffer,BUFSIZ)) > 0 ) {

			printf("Leyendo %d bytes de archivo %d\n",nbytes,fd[i]);
			nbytes=write(fddestino,buffer,nbytes);
			printf("Escribiendo %d bytes \n",nbytes);
		} /*while*/
		close(fd[i]);
	} /*for*/

	close(fddestino);

	exit(0);
}   
