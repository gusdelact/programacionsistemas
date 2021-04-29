#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

int serversocket; /*descriptor de socket para servidor*/
void fin(int signo) {
	close(serversocket);
	exit(0);
}


main() {
	int puerto=4000; /*puerto donde se escucha el servicio*/
	struct sockaddr_in sockaddr;
	char buffer[8092];
	struct sigaction accion; /*para manejar un sennal de 15*/

       	accion.sa_handler=fin;
	sigemptyset(&(accion.sa_mask));
	accion.sa_flags=0;
        sigaction(SIGTERM,&accion,(struct sigaction *)0);

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
		perror("error en bind\n"); exit(2);
	}


	if (listen(serversocket,5) ) {
		perror("error en listen"); exit(3);
	} else {
		struct sockaddr_in claddr;
		int rtn,len=sizeof(claddr);

		while ( (rtn= accept(serversocket,(struct sockaddr *)&claddr,&len)) > 0) {

		if (rtn < 0) {
                        perror("error en accept");
                } else {
                       char reply[] ="Content-type:text/html\n\n<html><body>Hello!!</body></html>\n";
                       int sd=rtn;
                        sprintf(buffer,"Cliente con datos IP:%s,puerto:%d se le asigna conexion con descriptor %d\n",
                        inet_ntoa(claddr.sin_addr),claddr.sin_port,rtn);
                        write(2,buffer,strlen(buffer));
                        if ((rtn=read(sd,buffer,sizeof(buffer)))>0 ) {
				buffer[rtn]=0;
                        	write(2,buffer,strlen(buffer));
				if (write(sd,reply,strlen(reply))<0) perror("write");
				else write(2,reply,strlen(reply));
  			} else { perror("read "); }
                        close(rtn);
                }
               }
	       if (rtn <0)  perror("Error en accept");
	}
	
	close(serversocket);
}
