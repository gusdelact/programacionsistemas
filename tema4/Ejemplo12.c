/*Ejemplo12 Uso de offset */

#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>

main( int argc, char * argv[]) {

	int fd, offset,nbytes,i;
	char buffer[16];

	if (argc==2) {
		printf("Ejemplo9: Ejemplo9 posicion archivo_a_recorrer\n");
		exit(1);
	} else {
		offset= atoi(argv[1]);
	}

	
	fd= open(argv[2],O_RDONLY);


	/*Posicionarse offset bytes, con respecto al origen*/

	printf("Offset relativo al inicio\n");
	offset=	lseek(fd,offset,SEEK_SET);

	if (offset < 0) {
		perror("Error en lseek SEEK_SET");
		exit(2);
	}
	
	nbytes=	read(fd,buffer,16);

	for (i=0;i<nbytes;i++) {
		printf("En posicion %d esta el caracter %c\n",offset+i,buffer[i]);
	}


	
	/*Posicionarse offset bytes, con respecto a la posicion actual*/
	printf("Offset relativo a la posicion actual\n");
	
	offset=	lseek(fd,offset,SEEK_CUR);

	if (offset < 0) {
		perror("Error en lseek SEEK_CUR");
		exit(3);
	}
	
	nbytes=	read(fd,buffer,20);

	for (i=0;i<nbytes;i++) {
		printf("En posicion %d esta el caracter %c\n",offset+i,buffer[i]);
	}


        /*Posicionarse offset bytes, con respecto al fin de archivo*/
	printf("Offset relativo al fin de archivo\n");

        offset= lseek(fd,-offset,SEEK_END);

        if (offset < 0) {
                perror("Error en lseek SEEK_EMD");
                exit(3);
        }

        nbytes= read(fd,buffer,20);

        for (i=0;i<nbytes;i++) {
                printf("En posicion %d esta el caracter %c\n",offset+i,buffer[i]
);
        }

	
}

