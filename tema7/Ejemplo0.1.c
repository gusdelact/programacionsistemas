/*Ejemplo1 Un proceso cliente se conecta al servicio de fecha de UNIX
por el puerto 13*/

#include <sys/socket.h>
#include <netinet/in.h>


main(){ 
	int puerto= 25; /*el puerto del servicio del correo es 25*/
	int sd; /*este es el descriptor de socket, se maneja como un
		archivo*/
	char ip[]="127.0.0.1";
	struct sockaddr_in sockaddr; /*estructura de datos para prover lo
				necesario para conectarse al servicio*/


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
	printf("Asi retorna inet_addr %x\n", inet_addr(ip));
	printf("Asi retorna htons %d\n", htons(puerto));
	sockaddr.sin_family=AF_INET; /*la direccion que se especifica 
					esta en formato IP*/
	sockaddr.sin_addr.s_addr= inet_addr(ip);
	sockaddr.sin_port=  htons(puerto);

	/*para conectarse, se debe utilizar la funcion connec,
	que recibe el socket descriptor, la estructura para realizar
	datos de conexion y el tamanno de la misma
	*/

	if (connect(sd,(struct sockaddr*)&sockaddr ,sizeof(sockaddr))) {
		perror("error al abrir conexion");
		exit(3);
	}

	/*siempre se debe cerrar la conexion*/
	close(sd);
}
