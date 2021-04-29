#include <sys/types.h>
#include <stropts.h>
#include <sys/conf.h>
#include <fcntl.h>

void informacionStreams(int fd) {
	int n_mods,i;
	struct str_list modulos;


	/*Checar si es un stream*/
	if (isastream(fd)) {
		printf("es una archivo de STREAMS\n");
	} else
		return;

	/*Obtener el numero de modulos
		Se utiliza ioctl sobre el descriptor de archivos,
		la peticion I_LIST indica que se desea conocer
		cuantos modulos de STREAMS estan dentro de
		este archivo, no se envia ningun argumento
	*/

	n_mods=ioctl(fd,I_LIST, NULL);

	if (n_mods < 0) {
		perror("No puedo contar modulos");
		exit(3);
	}

	printf("Numero Modulos %d\n",n_mods);

	/* La estructura str_list contiene la lista de cada modulo,
		este tiene esta organizada asi: 

		struct str_list {
			int sl_nmods;
			struct str_mlist *sl_modlist;
		};

	y la estructura str_mlist

		struct str_mlist {
		char l_name[FMNAMESZ+1];
		};

	*/

	/*Llenar la estructura indiando el numero de modulos*/
	modulos.sl_nmods=n_mods;
	/*y pasando el buffer de la lista de modulos*/
	modulos.sl_modlist= ( void *)calloc(n_mods,sizeof(struct str_mlist));

	/*ioctl con peticion I_LIST y estrutura str_list indica
	todos los modulos
	*/
	ioctl(fd,I_LIST,&modulos);

	/*Imprimir cada modulo*/
	for (i=0;i<n_mods;i++) 
		printf("%s\n",modulos.sl_modlist[i].l_name);

	close(fd);

}
main(int argc,char * argv[]) {

	int fd;
	if (argc==1) {
		printf("Ejemplo29: Ejemplo29 archivo");
		exit(1);
	}    
	fd=open(argv[1],O_RDONLY);
	if (fd < 0) {
		perror("No puedo abrir el archivo");
		exit(2);
	}

	informacionStreams(fd);
	informacionStreams(0);
	informacionStreams(1);
	exit(0);
}
