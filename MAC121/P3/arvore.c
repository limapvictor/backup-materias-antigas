#include <stdio.h>
#include <stdlib.h>

struct registro {
    int conteudo;
    struct registro *esq;
    struct registro *dir;
    struct registro *pai;
    int efio;
    int dfio;
};
typedef struct registro *no;

char corresp(int x)
{
    
    switch (x) {
        case 55: return 'A';
        case 33: return 'C';
        case 22: return 'B';
        case 44: return 'E';
        case 36: return 'G';
        case 15: return 'H';
        case 16: return 'J';
        case 18: return 'N';
        case 66: return 'D';
        case 100: return 'F';
        case 90: return 'I';
        case 80: return 'K';
        case 95: return 'L';
        case 75: return 'M';
        case 74: return 'O';
        case 76: return 'P';
    }
}

no insereArvore(no raiz, int x)
{
    if (raiz == NULL) {
        raiz = malloc (sizeof (struct registro));
        raiz->conteudo = x;
        raiz->esq = NULL; raiz->dir = NULL; 
        raiz->pai = NULL;
        return (raiz);
    }
    if (raiz->conteudo > x) {
        raiz->esq = insereArvore(raiz->esq, x);
        raiz->esq->pai = raiz;
    } else if (raiz->conteudo < x){
        raiz->dir = insereArvore(raiz->dir, x);
        raiz->dir->pai = raiz;
    }
    return (raiz);
}

no buscaArvore(no raiz, int x)
{
    if (raiz == NULL || raiz->conteudo == x) 
        return raiz;
    if (raiz->conteudo < x) 
        return (buscaArvore(raiz->dir, x));
    else 
        return (buscaArvore(raiz->esq, x));
}

no maximo(no raiz)
{
    if (raiz->dfio == 0 && raiz->dir != NULL)
        return (maximo(raiz->dir));
    return (raiz);
}

no minimo(no raiz)
{
    if (raiz->efio == 0 && raiz->esq != NULL)
        return (minimo(raiz->esq));
    return (raiz);
}

no removeArvore(no raiz, int x)
{
    no aux;
    if (raiz != NULL) {
        if (raiz->conteudo > x) {
            raiz->esq = removeArvore(raiz->esq, x);
        } else if (raiz->conteudo < x) {
            raiz->dir = removeArvore(raiz->dir, x); 
        } else {
            if (raiz->dir == NULL) {
                aux = raiz;
                raiz = raiz->esq;
                if (raiz != NULL)
                    raiz->pai = aux->pai;
                free(aux);
            } else if (raiz->esq == NULL) {
                aux = raiz;
                raiz = raiz->dir;
                raiz->pai = aux->pai;
                free(aux);
            } else {
                aux = maximo(raiz->esq);
                raiz->conteudo = aux->conteudo;
                raiz->esq = removeArvore(raiz->esq, aux->conteudo);
            }
            return (raiz);
        }
    }
}

int contaNos(no raiz)
{
    if (raiz != NULL)
        return (1 + contaNos(raiz->esq) + contaNos(raiz->dir));
}

int ancest(no x, no y)
{
    if (x == NULL)
        return (0);
    if (x == y) 
        return (1);
    if (x->conteudo < y->conteudo)
        return (ancest(x->dir, y));
    return (ancest(x->esq, y));
}

int ancestral(no x, no y)
{
    no p = y->pai;
    while (p != NULL) {
        if (p == x)
            return (1);
        p = p->pai;
    }
    return (0);
}

void inOrdem(no raiz)
{
    if (raiz != NULL) {
        inOrdem(raiz->esq);
        // printf("%c\t", corresp(raiz->conteudo));
        printf ("%d, ", raiz->conteudo);        
        inOrdem(raiz->dir);
    }
}

void preOrdem(no raiz)
{
    if (raiz != NULL) {
        // printf("%c ", corresp(raiz->conteudo));
        printf ("%d, ", raiz->conteudo);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

void posOrdem(no raiz)
{
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        // printf("%c ", corresp(raiz->conteudo));
        printf ("%d, ", raiz->conteudo);
    }
}

int profundidade(no x)
{
    if (x->pai != NULL)
        return (1 + profundidade(x->pai));
    return (0); 
}

no sucessor(no x)
{
    no p;
    if (x->dir != NULL)
        return (minimo(x->dir));
    else {
        p = x;
        while (p->pai != NULL && p->pai->dir == p)
            p = p->pai;
        return (p->pai);
    }
}

no antecessor(no x)
{
    no p;
    if (x->esq != NULL) 
        return (maximo(x->esq));
    else {
        p = x;
        while (p->pai != NULL && p->pai->esq == p)
            p = p->pai;
        return (p->pai);
    }
}

no sucessorPre(no x)
{
    no p;
    if (x->esq != NULL)
        return (x->esq);
    if (x->dir != NULL)
        return (x->dir);
    p = x;
    while (p->pai != NULL && p->pai->dir == p)
        p = p->pai;
    p = p->pai;
    return (p->dir);
}

int menorQue(no raiz, int x) 
{
    if (x > maximo(raiz)->conteudo)
        return (1);
    return (0);
}

int maiorQue(no raiz, int x)
{
    if (x < minimo(raiz)->conteudo)
        return (1);
    return (0);
}

int ehABB(no raiz)
{
    if (raiz != NULL) {
        if (raiz->esq != NULL && raiz->esq->conteudo > raiz->conteudo)
            return (0);
        if (raiz->dir != NULL && raiz->dir->conteudo < raiz->conteudo)
            return (0);
        return (ehABB(raiz->esq));
        return (ehABB(raiz->dir));
    }
    return (1);
}

int acha(int v[], int ini, int fim, int x)
{
    int i;
    for (i = ini; i < fim && v[i] != x; i++);
    return (i);
}

no remontaPreIn(int in[], int pre[], int *posPre, int iniIn, int fimIn)
{
    if (iniIn > fimIn) return (NULL);
    no raiz = malloc (sizeof (struct registro));
    raiz->conteudo = pre[*posPre]; *posPre += 1;
    int i = acha(in, iniIn, fimIn, raiz->conteudo);
    raiz->esq = remontaPreIn(in, pre, posPre, iniIn, i - 1);
    raiz->dir = remontaPreIn(in, pre, posPre, i + 1, fimIn);
    return (raiz);
}

no remontaPosIn(int in[], int pos[], int *posPos, int iniIn, int fimIn)
{
    if (iniIn > fimIn) return (NULL);
    no raiz = malloc (sizeof (struct registro));
    raiz->conteudo = pos[*posPos]; *posPos -= 1;
    int i = acha(in, iniIn, fimIn, raiz->conteudo);
    raiz->dir = remontaPosIn(in, pos, posPos, i + 1, fimIn);
    raiz->esq = remontaPosIn(in, pos, posPos, iniIn, i - 1);
    return (raiz);
}

void costuraArvore(no raiz)
{ 
    if (raiz->esq != NULL){
        raiz->efio = 0;
        costuraArvore(raiz->esq);
    } else if (raiz->esq == NULL) {
        raiz->efio = 1;
        raiz->esq = antecessor(raiz);
    }
    if (raiz->dir != NULL){
        // printf ("%d", raiz->conteudo);
        raiz->dfio = 0;
        costuraArvore(raiz->dir);
    } else if (raiz->dir == NULL) {
        raiz->dfio = 1;
        raiz->dir = sucessor(raiz);
    }
        
}

void printCosturada(no raiz)
{
    no p = minimo(raiz);
    while (p != NULL) {
        printf("%d ", p->conteudo);
        if (p->dfio == 1)
            p = p->dir;
        else
            p = minimo(p->dir);
    }
}

int main()
{
    no raiz = NULL, x, y;
    int v[12] = {50,30,70,20,40,60,80,15,25,35,45,36}, u[16] = {55,33,66,22,44,100,36,15,16,18,90,80,95,75,74,76};
    int uIn[16] = {15, 16, 18, 22, 33, 36, 44, 55, 66, 74, 75, 76, 80, 90, 95, 100},
        uPre[16] = {55, 33, 22, 15, 16, 18, 44, 36, 66, 100, 90, 80, 75, 74, 76, 95},
        uPos[16] = {18, 16, 15, 22, 36, 44, 33, 74, 76, 75, 80, 95, 90, 100, 66, 55};
    
    int j = 15;
    
    for (int i = 0; i < 12; i++) 
        raiz = insereArvore(raiz, v[i]);

    inOrdem(raiz); printf("\n");
    costuraArvore(raiz); printCosturada(raiz);
    // preOrdem(raiz); printf("\n");
    // posOrdem(raiz); printf("\n");

}