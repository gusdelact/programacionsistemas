#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

void tienepatron(char *directorio,char * archivo, char * patron) {

	int pid,rtn;

	pid= fork();

	if (pid< 0) {
		perror("Error en fork");
		return;
	}

	if (pid==0) {

		rtn=
		execl("/bin/grep","/bin/grep",patron,archivo,(char *) 0);
		if (rtn< 0) {
			perror("Error en grep");
			exit(2);
		}
	} else {
		waitpid(pid,(int *) 0, 0);
	}
}

void busca(char * directorio,char *patron) {
	DIR * direc;
	struct dirent * entrada;
	char * nombreentrada;
	struct stat buf;
	char * actual;
	int rtn;

	direc=opendir(directorio);

	if (direc == (DIR *) 0) {
		printf("No se puede manipular %s \n",directorio);
		return;
	}

	actual= getcwd((char *) 0, 1024);

	if (actual == (char *) 0) {
		perror("Error al obtener directorio actual");
		return;
	}

	rtn= chdir(directorio);
	if (rtn < 0) {
		perror("chdir");
		exit(1);
	}

	printf("Directorio %s\n",actual);

	while ( (entrada=readdir(direc) ) != (struct dirent *) 0 ) {
		nombreentrada=entrada->d_name;

		if ( 
			!strcmp(nombreentrada,".")
				|| 
		 	!strcmp(nombreentrada,"..")
		) 
			continue;

		printf("%s\n",nombreentrada);

		stat(nombreentrada,&buf);

		if (  (buf.st_mode&0xF000) == 0x4000  ) {
			busca(nombreentrada,patron);
		} else  {
			tienepatron(directorio,nombreentrada,patron);
		}	
	}

	closedir(direc);

	rtn= chdir(actual);
	if (rtn < 0) {
		perror("chdir");
		exit(1);
	}


	
	return;
}

main(int argc, char *argv[]) {

	char *directorio;
	char * patron;

	if (argc<3) {
		printf("Ejemplo31 patron directorio");
	}

	patron= argv[1];
	directorio=argv[2];

	busca(directorio,patron);	
}
