#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define CONTADOR "contador"

int fd;
int contador=0;

void *procesar(void * args) {
   char sContador[4]; /*contenido del archivo de maximo tres posiciones*/
   char mensaje[256]; /*buffer de mensaje para depurar*/
   while ( contador < 99){
      int nbytes;
      /*poner el descriptor al inicio del archivo*/
      if ( lseek(fd,0,SEEK_SET) ) perror("Error en lseek");
      /*leer el archivo*/
      nbytes= read(fd,sContador,sizeof(sContador));
      if (nbytes < 0)  {
		perror("Error al leer el archivo");
		exit(2);
      }
      sContador[nbytes-1]=0;
      sprintf(mensaje,"lee contador %s %d bytes\n",sContador,nbytes);	
      write(1,mensaje,strlen(mensaje));
      /*convertir el contador a entero*/
      contador=atoi(sContador);
      /*incrementar contador*/
      contador++;
      /*se escribe a salida estandar los mensajes*/
      sprintf(mensaje,"poner contador a valor %d\n", contador);
      write(1,mensaje,strlen(mensaje));
      /*escribir el resultado al inicio del archivo*/
      if ( lseek(fd,0,SEEK_SET) ) perror("Error en lseek");
      sprintf(sContador,"%d\n",contador);
      write(fd,sContador,strlen(sContador));     
   }
}

main(int argc, char * argv[]) {
   int nThreads,i; 
   pthread_t threads[128];
   
   if (argc <=1 ) {
	printf("Ejemplo1 nThreads\n");
	exit(1);
   }	
   nThreads=atoi(argv[1])-1;
   fd= open(CONTADOR, O_RDWR);

    if (fd < 0) {
	perror("Error al abir el archivo");
	exit(1);
    }

    for (i=0;i<nThreads;i++) {
        if (pthread_create(&threads[i],(pthread_attr_t *)0 ,procesar,0)<0) {
           perror("pthread_create"); exit(2);
        }
    }
    for (i=0;i<nThreads;i++) {
       int rtn;
       if (pthread_join(threads[i],(void **)(&rtn)) < 0) perror("pthread_join");
    }
    close(fd);  
}
