#include "Ejemplo11.h"

#define N 10

main(int argc, char * argv[]) {


	struct semaforo sem;
	int i,n;
	char buffer[128];

	if (argc <=1) {
		printf("Ejemplo13 n\n");
		exit(1);
	}

	n= atoi(argv[1]);

	sem.key=654321L;

	abreSemaforo(&sem);	

	if (sem.semId <0) {
		printf("error al crear semaforo\n");
		exit(1);
	}

	i=1;
	while (i<=n) {
		sprintf(buffer,"Subiendo semaforo por %d vez\n",i);	
		write(1,buffer,strlen(buffer));
		if ( V(&sem) < 0 ) {
			perror("error al subir el semaforo");
			exit(2);
		}
		i++;
	}
}
