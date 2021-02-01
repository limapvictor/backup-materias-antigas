struct registro {
    char *palavra;
    int cont;
    struct registro *esq;
    struct registro *dir;
};
typedef struct registro *no;

no insereArvore(no, char *, int *);

void imprimeInOrdem(no);

void deletaArvore(no);

no buscaArvore(no, char *);
