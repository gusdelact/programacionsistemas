/*definicion de un objeto semaforo binario*/

/*atributos o propiedades del objeto*/

struct semBinario {
	int key; /*llave como se conoce en el kernel*/
	int semId; /*identificador del semaforo*/
};

/*crear un semaforo dentro del kernel*/
extern void creaSemaforoBinario(struct semBinario * sembin);
/*subir al semaforo*/
extern int up(struct semBinario * sembin);
/*bajar al semaforo*/
extern int down(struct semBinario * sembin);
