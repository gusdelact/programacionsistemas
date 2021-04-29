#include "Ejemplo14.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>

void inserta(char *archivo,char *nombre, char * telefono) {

	struct telefonos nuevotelefono;
	int offset,fd,nbytes; 

	strcpy(nuevotelefono.nombre,nombre);
	strcpy(nuevotelefono.telefono,telefono);


	fd= open(archivo,O_WRONLY);

	if (fd <0 ) {
		perror("Error al abrir archivo");
		exit(3);
	}	

	offset=lseek(fd,0,SEEK_END);

	if (offset < 0) {
		perror("Error al posicionar el archivo");
		exit(4);
	}
	nbytes=write(fd,&nuevotelefono,sizeof(nuevotelefono));

	printf("Agregando %d bytes",nbytes);

	close(fd);

}

void registroEn(char * archivo,long index){

	int fd, offset,nbytes;
	struct telefonos registro;

	fd= open(archivo,O_RDONLY);

	if (fd <0 ) {
		perror("Error al abrir archivo o no existe");
		exit(3);
	}

	offset=lseek(fd, index*sizeof(struct telefonos),SEEK_SET);

	if (offset < 0) {
		perror("Error al posicionar el archivo");
		exit(4);
	}

	nbytes=read(fd,&registro,sizeof(struct telefonos));

	if (nbytes < 0) {
		perror("Error al leer");
		exit(5);
	}

	printf("Registro %d: Nombre %s Telefono %s\n",index,
		registro.nombre,registro.telefono);

	close(fd);

}

main(int argc,char *argv[]) {

	char * nombrearchivo=(char *)0;

	nombrearchivo= getenv("DIRECTORIO");	

	if (nombrearchivo== (char *) 0) {
		printf("Se debe definir la variable de ambiente DIRECTORIO");
		exit(2);
	}
	
	if (argc == 3) {
		inserta(nombrearchivo,argv[1],argv[2]);
	} else if (argc==2) {
		int pos;

		pos= atoi(argv[1]);
		registroEn(nombrearchivo,pos);
	} else {
		printf("Ejemplo14: Ejemplo14 nombre telefono | Ejemplo14 #registro\n");
	}



}
