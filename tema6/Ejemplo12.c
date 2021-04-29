#include "Ejemplo11.h"

#define N 10

main() {


	struct semaforo sem;
	int i;
	char buffer[128];

	sem.key=654321L;
	sem.valorinicial=N;

	creaSemaforo(&sem);	

	if (sem.semId <0) {
		printf("error al crear semaforo\n");
		exit(1);
	}

	i=1;
	while (i) {
		sprintf(buffer,"Intentando bajar semaforo por %d vez\n",i);	
		write(1,buffer,strlen(buffer));
		if ( P(&sem) <0){
			perror("Error en P");
			exit(2);
		}
		i++;
	}
}
