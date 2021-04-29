#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define MAXBUF 1024

main(int argc, char *argv[]) {
	int sockfd; /*descriptor de socket*/ 
	struct sockaddr_un serv_addr; /*estructura para configurar socket*/
	struct sockaddr_un cli_addr; /*estructura del cliente del socket*/
	int servlen; /*para calcuar la longitud de la estructura */
	int clilen;
	int newsockfd;
	char buffer[MAXBUF];
	int sz,i;

	if ( argc <= 1 ) {
		printf("Ejemplo21 rutasocket\n");
		exit(1);
	}
	sockfd = socket(AF_UNIX,SOCK_STREAM,0);
	
	if (sockfd < 0 ) {
		perror("servidor no puede abrir socket");
		exit(1);
	}
	printf("sockfd=%d\n",sockfd);	

	bzero( (char *) &serv_addr , sizeof(serv_addr) ); /*inicar a cero*/
	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, argv[1] ); /*indicar donde esta el socket*/
	servlen = strlen(serv_addr.sun_path) + sizeof (serv_addr.sun_family);

	if ( bind(sockfd, (struct sockaddr *) &serv_addr, servlen) < 0 ) {
		perror("servidor no aplica bind");
		exit(2);
	}
	listen(sockfd,5); /*escuchar 5 peticiones*/

	while (1) {
		clilen = sizeof(cli_addr);
		newsockfd=accept(sockfd, (struct sockaddr *) &cli_addr , &clilen );
		if ( newsockfd < 0 ) {
			perror("servidor error al recibir peticion del cliente");
			continue;
		}
		sz =read(newsockfd,buffer,MAXBUF);
		if (sz < 0 ) {
			 perror("servidor error en lectura"); 
		   close(newsockfd);
			continue;
		}
		if ( sz > MAXBUF ) sz = MAXBUF - 1;
		buffer[sz] = (char) 0;
		printf("mensaje %s\n",buffer);
		for ( i=0; i<strlen(buffer) ; i++)
			 buffer[i] = toupper(buffer[i]);
		if ( write(newsockfd,buffer,strlen(buffer)) < 0 ) {
			perror("servidor error en lectura"); 
		  close(newsockfd);
			continue;
		}
		close(newsockfd);
	}
	exit(0);
}
