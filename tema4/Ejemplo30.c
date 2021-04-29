#include <fcntl.h>
#include <sys/ttold.h>

main(int argc,char * argv[]) {

	int fd;
	int rtn;
	struct sgttyb configuracion;

	if (argc==1) {
		printf("Ejemplo29: Ejemplo29 archivo");
		exit(1);
	}    
	fd=open(argv[1],O_RDONLY);

	if (fd < 0) {
		perror("No puedo abrir el archivo");
		exit(2);
	}

	if (isastream(fd)) {
		printf("%s es una archivo de STREAMS\n",argv[1]);
	}else {
		exit(3);
	}

	rtn=ioctl(fd,TIOCGETP,&configuracion);	
	if (rtn<0) {
		perror("Error en ioctl TIOCGETP");
		exit(4);
	}
	printf("Configuracion actual de la terminal %s",argv[1]);

	printf("sg_ispeed %x ", configuracion.sg_ispeed);
	printf("sg_ospeed %x ", configuracion.sg_ospeed);
	printf("erase %x ", configuracion.sg_erase);
	printf("kill %x\n ", configuracion.sg_kill);
	configuracion.sg_erase='z';
	configuracion.sg_kill='w';

	rtn=ioctl(fd,TIOCSETP,&configuracion);	

	if (rtn<0) {
		perror("Error en ioctl TIOCSETP");
		exit(4);
	}
	close(fd);

	exit(0);

}
