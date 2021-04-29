#include <sys/socket.h>
#include <netinet/in.h>


main(int argc,char * argv[]){ /*la direccion IP se obtiene en el primer 
				argumento
				*/
	int puerto= 25; /*el puerto del servicio del tiempo es 13*/
	int sd; /*este es el descriptor de socket, se maneja como un
		archivo*/
	struct sockaddr_in sockaddr; /*estructura de datos para prover lo
				necesario para conectarse al servicio*/
	int nbytes;
	char buffer[128];

	if (argc<=1) {
		printf("Ejemplo4 <direccionIP>\n");
		exit(1);
	}

	/* se abre un socket que direcciona la informacion 
	a una nodo con direccion IP, por tanto se indica AF_INET.
	Se utiliza TCP. por tanto el modo de conexion es orientado
	a flujo de bytes.
	El tercer parametro se pone a 0 para dejar que el kernel
	utilice el protocolo por omision, en esta caso TCP/IP
	*/
	sd=socket(AF_INET,SOCK_STREAM,0);
	
	if (sd < 0) { /*se checa que no exista error*/
		perror("Error al abrir socket");
		exit(2); 	
	}

	/*los siguientes pasos preperan la informacion para que el kernel
	conozca como debe conectarse al otro nodo
	una estructura sockaddr debe indicar el tipo de direccion,
	la direccion IP y el puerto
	*/
	sockaddr.sin_family=AF_INET; /*la direccion que se especifica 
					esta en formato IP*/
	sockaddr.sin_addr.s_addr= inet_addr(argv[1]);
	sockaddr.sin_port=  htons(puerto);

	/*para conectarse, se debe utilizar la funcion connec,
	que recibe el socket descriptor, la estructura para realizar
	datos de conexion y el tamanno de la misma
	*/

	if (connect(sd,(struct sockaddr*)&sockaddr ,sizeof(sockaddr))) {
		perror("error al abrir conexion");
		exit(3);
	}

	/*leer primer token,presentacion del servicio de correo*/
	nbytes=read(sd,buffer,128);
	write(2,buffer,nbytes);	

	/*presentarse con servicio de correo*/
	sprintf(buffer,"HELO abc.com\n");
	write(sd,buffer,strlen(buffer));

	/*leer segundo token, contestacion a HELO*/
	nbytes=read(sd,buffer,128);
	write(2,buffer,nbytes);	

	/*indicarle de quien viene el mail*/
	sprintf(buffer,"MAIL FROM:<clinton@whitehouse.gov>\n");
	write(sd,buffer,strlen(buffer));
	
	/*leer tercer token, contestacion a MAIL FROM*/
	nbytes=read(sd,buffer,128);
	write(2,buffer,nbytes);	

	/*indicarle a quien viene el mail*/
	sprintf(buffer,"RCPT TO:<root>\n");
	write(sd,buffer,strlen(buffer));
	
	/*leer cuarto token, contestacion a RCPT TO*/
	nbytes=read(sd,buffer,128);
	write(2,buffer,nbytes);	

	/*indicarle los datos*/
	sprintf(buffer,"DATA\nI love Monica\n.\n");
	write(sd,buffer,strlen(buffer));
	
	/*leer quinto token, contestacion a DATA*/
	nbytes=read(sd,buffer,128);
	write(2,buffer,nbytes);	

	/*despedirse*/
	sprintf(buffer,"QUIT\n");
	write(sd,buffer,strlen(buffer));
	
	/*leer sexto token, contestacion a DATA*/
	nbytes=read(sd,buffer,128);
	write(2,buffer,nbytes);	



	/*siempre se debe cerrar la conexion*/
	close(sd);
}
