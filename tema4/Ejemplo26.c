#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc,char * argv[]) {
	int fd,fd2;
	int nbytes;
	char buffer[128];

	if (argc==1) {
		printf("Ejemplo25: Ejemplo25 archivolectura");
		exit(1);
	}

	/*Abrir el archivo indicado*/
	fd = creat(argv[1],0644);

	fd2=dup2(fd,1);

	if (fd2 < 0) {
		perror("No es posible redireccionar la entada");
		exit(2);
	}

	printf("%d\n",fd2);

	while ( ( nbytes = read(0,buffer,sizeof(buffer)) ) > 0 ) {
		write(1,buffer,nbytes);
	}

	exit(0);

}
