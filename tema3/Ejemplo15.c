#define MAXARGSZ 1024
#define MAXARGS 128

void leer_comando( char  *argumentos[]) {
	char cmd[MAXARGSZ];
	int argc=0;
	int i;
	extern char *strtok(char *, const char *);
	char *ptok;

	gets(cmd);

	ptok =strtok(cmd," ");
	while (  1 ) {
		argumentos[argc] =ptok;
		argc++;
		if (ptok != (char *)0) {
			ptok=strtok((char *)0," ");
		} else
			break;
	}

	argumentos[argc]=(char *)0;

}

main() {

	char prompt[]="gush% ";

	while (1) {
		char  * args[MAXARGS];
		char bg;
		int pid;

		write(1,prompt,sizeof(prompt));
		leer_comando(args);	

		pid= fork();

		if (pid==0) {
			int rtn;
			rtn=execvp(args[0],&args[0]);
			if (rtn==-1)
				perror(args[0]);
		}

	}
}
