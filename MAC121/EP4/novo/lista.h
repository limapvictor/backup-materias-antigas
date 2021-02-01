struct celula {
    char *palavra;
    int cont;
    struct celula *prox;
};
typedef struct celula *apontador;

apontador insereListaDesordenada(apontador, char *);

apontador insereListaOrdenada(apontador, char *);

apontador intercalaLista(apontador, apontador, char);

apontador mergeSortLista(apontador, char);

void imprimeListaOrdenada(apontador);

apontador buscaLista(apontador, char *);