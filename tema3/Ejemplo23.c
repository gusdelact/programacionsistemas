#define MAXCMD 128
#define CMDGET "GET"
#define CMDPOST "POST"
#define CMDFORGET "/bin/cat"

void procesoDemonio(void) {

	int pid;

	pid=fork();
	if (pid ==0) {
		printf("Proceso demonio con PID %d\n",getpid());
		return;
	} else {
		exit(0);
	}
}

void finHijo(void) {
	printf("Proceso Hijo %d concluye\n",getpid());
}

void procesaComando(char *cmd ) {

	int pid=fork();
	extern char * strstr(const char *,const char *);

	if (pid < 0) {

	} else if (pid == 0) {
		char* archivo=(char *)0;
		int rtn;
		atexit(finHijo);
		printf("PID %d procesando %s\n",getpid(),cmd);

		if ( archivo=strstr(cmd,CMDGET) ) {
			printf("GET %s",archivo+4);	
			rtn=execlp(CMDFORGET,"GET",archivo+4,(char *)0);
			if (rtn==-1) {
				perror("Error en GET");
				exit(2);
			}
		}else if ( archivo=strstr(cmd,CMDPOST) ) {
			printf("POST %s ",archivo+5);	
			rtn-execlp(archivo+5,"POST",(char *)0);
			if (rtn==-1) {
				perror("Error en POST");
				exit(3);
			}

		} else {
			printf("Directiva desconocida ");
			exit(1);
		}	

		exit(0);
	} 

	return;
}

void esperaTransaccion() {
	char cmd[MAXCMD];
	extern char *gets(char *);
	while (1) {
		char *ptr;
		printf("Esperando transaccion ...\n");
		ptr=gets(cmd);

		if (ptr) {
			procesaComando(cmd);
		}
	}
}

main() {

	procesoDemonio();
	esperaTransaccion();
}
