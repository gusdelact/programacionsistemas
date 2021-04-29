#include <sys/types.h>
#include <sys/stat.h>

void informacionarchivo(const char * archivo) {
	int rtn;
        struct stat buf;

	rtn=stat(archivo,&buf);
	if (rtn< 0) {
                perror("Error en stat");
                exit(1);
        }

	printf("%s\n",archivo);
        printf("Modo %x\n",buf.st_mode&0xF000);
        printf("Permisos %o\n",buf.st_mode&0x1FF);
        printf("Inodo %d\n",buf.st_ino);
        printf("ID Device %d\n",buf.st_dev);
        printf("Numero de referencias %d\n",buf.st_nlink);
        printf("Propietario %d\n",buf.st_uid);
        printf("Grupo %d\n",buf.st_gid);
        printf("Tamanno %d\n",buf.st_size);
        printf("Ultimo acceso %d\n",buf.st_atime);
        printf("Ultima modificacion %d\n",buf.st_mtime);
        printf("Ultimo cambio %d\n",buf.st_ctime);
        printf("Tamanno bloque %d\n",buf.st_blksize);
        printf("Numero bloques %d\n",buf.st_blocks);


}
main() {

	int rtn;
	struct stat buf;

	informacionarchivo("/etc/passwd");
	informacionarchivo("/tmp");
	informacionarchivo("/dev/console");

	exit(0);	
}
