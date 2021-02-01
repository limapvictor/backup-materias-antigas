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
        printf("hm");
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

void inverteFrase(char frase[]) {
    Pilha p = criaPilha(100);
    int i;
    char c;
    for (i = 0; frase[i] != '.'; i++) {
        if (frase[i] != ' ') {
            empilha(p, frase[i]);
        } else {
            c = topoDaPilha(p);
            while (!pilhaVazia(p)) {
                printf("%c", c);
                desempilha(p);
                c = topoDaPilha(p);
            }
            printf(" ");
        }
    }
    destroiPilha(p);
}

void main(void) {
    inverteFrase("Este exercicio eh muito facil.");
}