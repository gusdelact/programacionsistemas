
main(int argc,char *argv[]){

	if (argc==1) {
		printf("Uso: Ejemplo21 PID");
	} else {
		int rtn;
		int pid= atoi(argv[1]);
		rtn=kill(pid,9);

		if (rtn<0)
			perror("No puedo matar al proceso");
		
	}

	exit(0);

}
