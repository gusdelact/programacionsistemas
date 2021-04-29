#include <stdlib.h>
#include <mysql.h>

main() {

	MYSQL * conn_ptr;

	conn_ptr = mysql_init(NULL);

	if ( !conn_ptr ) {
		perror("No puede aplicar mysql_init");
		exit(1);
	}

conn_ptr = mysql_real_connect(conn_ptr,"localhost","u900560","bar","test",0,NULL,0);
	if (conn_ptr) {
		printf("Conectado a base de datos");
	} else {
		perror("No puede aplicar mysql_init");
	}

	mysql_close(conn_ptr);
}
