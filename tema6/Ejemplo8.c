#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

main(int argc, char *argv[]) {

	int shid;
	int i;
	char * buffer;
	int sz;

	if (argc<=1) {
		printf("Ejemplo8 tamanno");
		exit(2);
	}

	/*el tamanno del segmento se obtiene como argumento*/
	sz=atoi(argv[1]);
	
	/*conectarse el segmento de memoria compartida*/
	shid= shmget(123456L,sz,0); 

	if (shid < 0) {
		perror("Error al obtener el segmento de memoria compartida");
		exit(3);
	}

	printf("Segmento %d con tamanno %d\n",shid,sz);

	/*obtener el apuntador al segmento*/
	buffer= (char *)shmat(shid,(void *) 0, 0);

	if (buffer < 0) {
		perror("Error en shmat");
		exit(4);
	}

	/*leer el buffer, caracter por caracter*/
	i=0;
	while (i<sz) {

		if (buffer[i]==0)
			break;
		printf("%c",buffer[i]);
		i++;
	}

	printf("\nArchivo cargado\n");

	if (shmdt(buffer) < 0) {
		perror("Error en shmdt");
		exit(6);
	}

	exit(0);
}
