#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define MAXBUF 1024

main(int argc, char *argv[]) {
	int sockfd; /*descriptor de socket*/
	struct sockaddr_un serv_addr; /*estructura para configurar socket*/
	int servlen;
	int sz;
	char msg[] = "hola mundo";
	char buffer[MAXBUF];	

	if ( argc <= 1 ) {
    	  printf("Ejemplo21 rutasocket\n");
    	  exit(1);
  	}

	sockfd = socket(AF_UNIX,SOCK_STREAM,0);
	if (sockfd < 0 ) {
		perror("cliente no puede abrir socket");
		exit(1);
	}
	printf("sockfd=%d\n",sockfd);

	bzero( (char *) &serv_addr , sizeof(serv_addr) ); /*inicar a cero*/
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, argv[1] ); /*indicar donde esta el socket*/
	servlen = strlen(serv_addr.sun_path) + sizeof (serv_addr.sun_family);
	
	if ( connect(sockfd,(struct sockaddr *) &serv_addr, servlen) < 0 ) {
		perror("cliente no puede abrir socket");
		exit(2);
	}
	if ( write(sockfd,msg,strlen(msg)) < 0 ) {
		perror("cliente error al escribir el mensaje");
		close(sockfd);
		exit(3);
	}
	sz = read(sockfd,buffer,MAXBUF);
	if ( sz < 0 ) {
		perror("cliente error al leer el mensaje");
		close(sockfd);
		exit(4);
	}
	if ( sz > MAXBUF ) sz = MAXBUF - 1;
	buffer[sz] = (char) 0;
	printf("%s\n",buffer);
	close(sockfd);	
	exit(0);
}
