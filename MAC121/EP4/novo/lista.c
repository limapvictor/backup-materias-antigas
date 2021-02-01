#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

apontador insereListaDesordenada(apontador inicio, char *palavra)
{
    apontador novo;
    if (inicio == NULL) {
        novo = malloc (sizeof (struct celula));
        novo->palavra = malloc ((strlen (palavra) + 1) * sizeof (char)); strcpy (novo->palavra, palavra);
        novo->cont = 1;
        novo->prox = NULL;
        return (novo);
    }
    if (strcoll (palavra, inicio->palavra) == 0) {
        inicio->cont += 1;
        return (inicio);
    }
    inicio->prox = insereListaDesordenada(inicio->prox, palavra);
    return (inicio);
}

apontador insereListaOrdenada(apontador inicio, char *palavra)
{
    apontador novo;
    if (inicio == NULL || strcoll (inicio->palavra, palavra) != -1) {
        if (inicio != NULL && strcoll (inicio->palavra, palavra) == 0) {
            inicio->cont += 1;
        } else {
            novo = malloc (sizeof (struct celula));
            novo->palavra = malloc ((strlen (palavra) + 1) * sizeof (char)); strcpy (novo->palavra, palavra);
            novo->cont = 1;
            novo->prox = inicio;
            return (novo);
        }
    } else {
        inicio->prox = insereListaOrdenada(inicio->prox, palavra);
        return (inicio);
    }
    return (inicio);
}

apontador intercalaLista(apontador p, apontador q, char ordem)
{
    apontador inicio, aux;
    inicio = aux = NULL;
    while (p != NULL && q != NULL) {
        if ((ordem == 'A' && strcoll (p->palavra, q->palavra) < 0) || (ordem == 'O' && p->cont > q ->cont)) {
            if (aux == NULL) {
                inicio = aux = p;
            } else {
                aux->prox = p; aux = p;
            }
            p = p->prox;
        } else {
           if (aux == NULL) {
                inicio = aux = q;
            } else {
                aux->prox = q; aux = q;
            }
            q = q->prox;
        }
    }
    if (p == NULL) {
        if (aux == NULL) inicio = q;
        else aux->prox = q;
    }
    if (q == NULL) {
        if (aux == NULL) inicio = p;
        else aux->prox = p;
    }
    return (inicio);
}

apontador mergeSortLista(apontador inicio, char ordem)
{
    apontador p, q;
    if (inicio == NULL || inicio->prox == NULL) return (inicio);
    p = inicio; q = inicio->prox;
    while (q != NULL && q->prox != NULL) {
        inicio = inicio->prox;
        q = q->prox->prox;
    }
    q = inicio->prox;
    inicio->prox = NULL;
    return (intercalaLista(mergeSortLista(p, ordem), mergeSortLista(q, ordem), ordem));
}

void imprimeListaOrdenada(apontador inicio)
{
    apontador p = inicio, aux;
    while (p != NULL) {
        printf ("%s %d \n", p->palavra, p->cont);
        aux = p;
        p = p->prox;
        free (aux->palavra); free (aux);
    }
}

apontador buscaLista(apontador inicio, char *p)
{
    apontador aux;
    for (aux = inicio; aux != NULL && strcoll (aux->palavra, p) != 0; aux = aux->prox);
    return (aux);
}
