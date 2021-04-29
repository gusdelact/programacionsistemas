#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc,char * argv[]) {
	int fdin,fdout,fd1,fd2;
	int nbytes;
	char buffer[128];

	if (argc<=2) {
		printf("Ejemplo25: Ejemplo25 archivolectura archivoescritura");
		exit(1);
	}

	/*Abrir los archivo indicado*/
	fdin = open(argv[1],O_RDONLY);

	if (fdin< 0) {
		perror("No es posible leer el archivolectura");
		exit(2);
	}

	fdout= creat(argv[2],0644);
	if (fdout< 0) {
		perror("No es posible escribir al archivoescritura");
		exit(3);
	}

	/*duplicar la entrada estandar en el descriptor fdin*/
	fd1= dup2(fdin,0);
	if (fd1 < 0) {
		perror("No es posible redireccionar la entrada estandar");
		exit(4);
	}
	/*duplicar la salida estandar en el descriptor fdout*/
	fd2=dup2(fdout,1);

	if (fd2 < 0) {
		perror("No es posible redireccionar la entada");
		exit(5);
	}


	while ( ( nbytes = read(0,buffer,sizeof(buffer)) ) > 0 ) {
		write(1,buffer,nbytes);
	}

	exit(0);

}
