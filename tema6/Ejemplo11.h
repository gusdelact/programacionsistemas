/*definicion de un objeto semaforo binario*/

/*atributos o propiedades del objeto*/

struct semaforo {
	int key; /*llave como se conoce en el kernel*/
	int semId; /*identificador del semaforo*/
	int valorinicial; /*valor del semaforo*/
};

/*crear un semaforo dentro del kernel*/
extern void creaSemaforo(struct semaforo * sem);
/*abrir semaforo*/
extern void abreSemaforo(struct semaforo * sem );
/*subir al semaforo*/
extern int V(struct semaforo * sem);
/*bajar al semaforo*/
extern int P(struct semaforo * sem);
