#include  <unistd.h>
#include  <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define PIPEPUBLISH "/tmp/ppublish"

#define MAXLEN 1024
struct mensajePublicador {
        char mensaje[MAXLEN]; /* se escribe un mensaje de cualquier tipo de
                                datos*/
};


main(int argc, char *argv[]) {

	int fd;
	struct mensajePublicador mensaje;
	int nbytes;

	if (argc <=1) {
	        strcpy(mensaje.mensaje,"hola mundo\n");
	} else {
	        strcpy(mensaje.mensaje,argv[1]);

	}

	fd= open(PIPEPUBLISH,O_WRONLY);

	if (fd < 0) {
		perror("Error al abrir pipe publicacion");
		exit(2);
	}


	nbytes=write(fd,&mensaje,sizeof(struct mensajePublicador));

	if (nbytes< 0) {
		perror("no se puede enviar el mensaje");
	} else {
		printf("Mensaje enviado\n");
	}
	close(fd);

	exit(0);
}
