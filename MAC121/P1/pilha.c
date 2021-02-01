#include <stdio.h>
#include <stdlib.h>

typedef struct {
        char *v;
        int topo;
        int max; } pilha;
typedef pilha *Pilha;

int pilhaVazia(Pilha P) {
    return (P->topo == 0);
}

void empilha(Pilha P, char el) {
    if (P->topo == P->max) {
        resize(P);
    } else {
        P->v[P->topo] = el;
        (P->topo)++;
    }
}

void desempilha(Pilha P) {
    if (pilhaVazia(P)) {
        printf("Erro");
        return;
    }
    (P->topo)--;
}

char topoDaPilha(Pilha P) {
    if (pilhaVazia(P)) {
        printf("Erro");
        return (0);
    }
    return (P->v[P->topo-1]);
}

Pilha criaPilha(int max) {
    Pilha P = malloc(sizeof(pilha));
    P->v = malloc(max * sizeof(char));
    P->topo = 0;
    P->max = max;
    return (P);
}

void destroiPilha(Pilha P) {
    free(P);
}

void resize(Pilha P) {
    int i;
    char *novo = malloc(2 * P->max * sizeof(char));
    for (i = 0; i < P->max; i++) {
        novo[i] = P->V[i];
    }
    P->max = 2 * P->max;
    free(P->v);
    P->v = novo;
}