#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

no insereArvore(no raiz, char *palavra, int *cont)
{
    if (raiz == NULL) {
        raiz = malloc (sizeof (struct registro));
        raiz->palavra = malloc ((strlen (palavra) + 1) * sizeof (char)); strcpy (raiz->palavra, palavra);
        raiz->cont = 1;
        raiz->esq = NULL; raiz->dir = NULL; 
        *cont += 1;
        return (raiz);
    }
    if (strcoll (raiz->palavra, palavra) == 0) {
        raiz->cont += 1;
    } else if (strcoll (raiz->palavra, palavra) > 0) {
        raiz->esq = insereArvore(raiz->esq, palavra, cont);
    } else {
        raiz->dir = insereArvore(raiz->dir, palavra, cont);
    }
    return (raiz);
}

void imprimeInOrdem(no raiz)
{
    if (raiz != NULL) {
        imprimeInOrdem(raiz->esq);
        printf ("%s %d\n", raiz->palavra, raiz->cont);
        imprimeInOrdem(raiz->dir);
    }
}

void deletaArvore(no raiz)
{
    if (raiz != NULL) {
        deletaArvore(raiz->esq);
        deletaArvore(raiz->dir);
        free (raiz->palavra); free (raiz);
    }
}

no buscaArvore(no raiz, char *p)
{
    if (raiz == NULL || strcoll (raiz->palavra, p) == 0) 
        return raiz;
    if (strcoll (raiz->palavra, p) < 0) 
        return (buscaArvore(raiz->dir, p));
    else 
        return (buscaArvore(raiz->esq, p));
}