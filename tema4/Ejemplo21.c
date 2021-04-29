#include <unistd.h>
/*Ejemplo21 Borrardo de un directorio*/

main() {

	int rtn;

	rtn= rmdir("/tmp/980432");

	if (rtn < 0) {
		perror("No se puede borrar el directorio /tmp/980432");
		exit(1);
	}

	exit(0);
}
