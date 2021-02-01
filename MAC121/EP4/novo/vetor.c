#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"

int insereVetorDesordenado(item *vetor, int *n, int contador, char *palavra)
{
    if (contador == *n - 1) {
        *n *= 2;
        vetor = realloc (vetor, *n);
    }
    int i;
    for (i = 0; i < contador && strcoll (palavra, vetor[i].palavra) != 0; i++);
    if (i != contador && strcoll (palavra, vetor[i].palavra) == 0) {
        vetor[i].cont += 1;
        return (contador);
    } else {
        vetor[i].palavra = malloc ((strlen (palavra) + 1) * sizeof (char)); strcpy (vetor[i].palavra, palavra);
        vetor[i].cont = 1;
        return (contador + 1);
    }
}

int insereVetorOrdenado(item *vetor, int *n, int contador, char *palavra)
{
    if (contador == *n - 1) {
        *n *= 2;
        vetor = realloc (vetor, *n);
    }
    int i, j;
    for (i = 0; i < contador && strcoll (palavra, vetor[i].palavra) > 0; i++);
    if (i != contador && strcoll (palavra, vetor[i].palavra) == 0) {
        vetor[i].cont += 1;
        return (contador);
    } else {
        for (j = contador; j > i; j--) {
            vetor[j] = vetor[j - 1];
        }
        vetor[i].palavra = malloc ((strlen (palavra) + 1) * sizeof (char)); strcpy (vetor[i].palavra, palavra);
        vetor[i].cont = 1;
        return (contador + 1);
    }
}

void troca(item *v, int i, int j)
{
    item aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int separa(item *v, int ini, int fim, char ordem)
{
    item pivo = v[fim - 1];
    int i = ini - 1, j;
    for (j = ini; j < fim; j++) {
        if ((ordem == 'A' && strcoll (v[j].palavra, pivo.palavra) <= 0 ) || (ordem == 'O' && v[j].cont >= pivo.cont)) {
            i++;
            troca(v, i, j);
        }
    }
    return (i);
}

void quickSort(item *v, int ini, int fim, char ordem)
{
    int pivo;
    if (fim - ini >= 2) {
        pivo = separa(v, ini, fim, ordem);
        quickSort(v, ini, pivo, ordem);
        quickSort(v, pivo + 1, fim, ordem);
    }
}

void imprimeVetorOrdenado(item *vetor, int contador, int tipo)
{
    int i;
    for (i = 0; i < contador; i++) {
        printf ("%s %d \n", vetor[i].palavra, vetor[i].cont);
        if (tipo != 10)
            free (vetor[i].palavra);
    }
    free (vetor);
}

int buscaDesordenada(item *v, int contador, char *p)
{
    int i;
    for (i = 0; i < contador; i++) {
        if (strcoll (v[i].palavra, p) == 0)
            return (i);
    }
    return (-1);
}

// int buscaBinaria(item *v, int ini, int fim, char *p)
// {
//     if (ini > fim) return (-1);
//     int meio = (ini + fim) / 2;
//     if (strcoll (v[meio].palavra, p) == 0) return (meio);
//     else if (strcoll (v[meio].palavra, p) > 0) return (buscaBinaria(v, ini, meio, p));
//     else return (buscaBinaria(v, meio + 1, fim, p));
// }

int buscaBinaria(item *v, int contador, char *p)
{
    int ini = 0, fim = contador - 1, meio, comp;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        comp = strcoll (v[meio].palavra, p);
        if (comp == 0) {
            return (meio);
        } else if (comp < 0 ) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return (-1);
}