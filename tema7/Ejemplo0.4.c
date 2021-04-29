#include <sys/socket.h>
#include <signal.h>

#include <netinet/in.h>



main() {
	int serversocket; /*descriptor de socket para servidor*/
	int puerto=4000; /*puerto donde se escucha el servicio*/
	struct sockaddr_in sockaddr;
	char buffer[128];

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
	}


	if (listen(serversocket,5) ) {
		perror("error en listen");
	} else {
		struct sockaddr_in claddr;
		int rtn,len=sizeof(claddr);

		 rtn=
                accept(serversocket,(struct sockaddr *)&claddr,&len);

		if (rtn < 0) {
                        perror("error en accept");
                } else {
                        sprintf(buffer,"Cliente con datos IP:%s,puerto:%d se le asigna conexion con descriptor %d\n",
                        inet_ntoa(claddr.sin_addr),claddr.sin_port,rtn);
                        write(2,buffer,strlen(buffer));
                        close(rtn);
                }
	}

	
	close(serversocket);
}
