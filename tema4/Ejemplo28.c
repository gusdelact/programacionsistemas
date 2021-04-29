#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

main(int argc,char * argv[]) {
	int fd,fd2;
	int nbytes;
	char buffer[128];
	int fd_flags;
	int rtn;

	/*Conoceer las banderas del archivo*/
	fd_flags= fcntl(0, F_GETFL,0);

	printf("flags %x\n",fd_flags&O_ACCMODE);
	if (fd_flags<0) {
		perror("Error en fcntl");
		exit(3);
	}

	/*Indicar que no se bloquee ante un read*/
	fd_flags|=O_NONBLOCK;
	printf("flags %x\n",fd_flags&O_ACCMODE);

	fcntl(0,F_SETFL, fd_flags);

	if (rtn < 1) {
		perror("No puedo poner nuevas banderas");
	}

	while ( 1  ) {
		char cmd[128];
		int nbytes;

		/*No se espera a que se le teclee algo*/
                nbytes=read(0,cmd, 128);

		if ( nbytes >0) {
			write(1,cmd,nbytes);
			exit(0);
		 }else {
			printf("Teclear algo para salir\n");
		}
	}




}
