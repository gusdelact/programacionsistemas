#include <sys/socket.h>
#include <signal.h>

#include <netinet/in.h>

int serversocket; /*descriptor de socket para servidor*/

void fin(int signo) {
	close(serversocket);
	exit(0);
}

main(int argc,char * argv[]) {
	int sock; /*descriptor de socket para cada conexion*/
	int puerto; /*puerto donde se escucha el servicio*/
	struct sockaddr_in sockaddr;
	struct sigaction accion; /*para manejar un sennal de 15*/

	if (argc <=1) {
		printf("Ejemplo8 <puerto>\n");
		exit(1);
	}

	accion.sa_handler=fin;
	sigemptyset(&(accion.sa_mask));
	accion.sa_flags=0;

	sigaction(SIGTERM,&accion,(struct sigaction *)0);
 
	puerto=atoi(argv[1]);

	serversocket=socket(AF_INET,SOCK_STREAM,0); /*abrir socket 
					para servidor*/	

	/*llenar estructura para ligar el socket con el puerto TCP*/	
	sockaddr.sin_family= AF_INET; /*utilizar direccion con formato IP*/
	sockaddr.sin_addr.s_addr= htonl(0x00000000); /*ligar socket 
					a cualquier direccion (0.0.0.0)posible
					de la maquina*/
	sockaddr.sin_port= htons(puerto);

	/*aplicar la asociacion con el puerto*/
	if (
	 bind(serversocket, ( struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0
	) {
		perror("error en bind\n");
		exit(2);
	}


	/*indica al sistema operativo que debe poner el socket en estado de 
	LISTEN*/
	if ( listen(serversocket,5) < 0) {
		perror("error en listen");
		exit(3);
	}

	/*esperar conexion*/

	while (1) {
		struct sockaddr_in claddr;
		int rtn,len=sizeof(claddr);
		char buffer[128];
		/*ejecutar la instruccion accept para
		recibir conexion TCP de un cliente*/
		rtn=
		accept(serversocket,(struct sockaddr *)&claddr,&len);
		if (rtn < 0) {
			perror("error en accept");
		} else {	
			int pid;
			sprintf(buffer,"Cliente con datos IP:%s,puerto:%d\n",
			inet_ntoa(claddr.sin_addr),claddr.sin_port);
			write(2,buffer,strlen(buffer));
			sock=rtn;

			pid=fork();
			if (pid < 0) {
				perror("no se pueda procesar peticion");
				continue;	
			} else if (pid==0) {
				int nbytes;
				nbytes=read(sock,buffer,128);
				
				if (nbytes < 0) {
					perror("error en lectura de peticion");
					exit(3);
				} else {
					int i;
					buffer[nbytes]=0;

					for (i=0;i< strlen(buffer);i++)
						buffer[i]=toupper( buffer[i]);
					write(sock,buffer,strlen(buffer));
				}
				close(sock); /*se cierra el socket*/	
				exit(0);
			} else {
				close(sock); /*proceso padre cierra socket*/
			}
		}
	}

	close(serversocket);
}
