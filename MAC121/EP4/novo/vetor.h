typedef struct {
    char *palavra;
    int cont;
} item;

int insereVetorDesordenado(item *, int *, int, char *);

int insereVetorOrdenado(item *, int *, int, char *);

void imprimeVetorOrdenado(item *, int, int);

void troca(item *, int, int);

int separa(item *, int, int, char);

void quickSort(item *, int, int, char);

int buscaDesordenada(item *, int, char *);

int buscaBinaria(item *, int, char *);
