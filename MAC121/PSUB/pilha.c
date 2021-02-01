#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        char *v;
        int topo;
        int max; } pilha;
typedef pilha *Pilha;

int pilhaVazia(Pilha P) {
    return (P->topo == 0);
}

void empilha(Pilha P, int el) {
    if (P->topo == P->max) {
        return;
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

int topoDaPilha(Pilha P) {
    if (pilhaVazia(P)) {
        printf("Erro");
        return (0);
    }
    return (P->v[P->topo-1]);
}

Pilha criaPilha(int max) {
    Pilha P = malloc(sizeof(pilha));
    P->v = malloc(max * sizeof(int));
    P->topo = 0;
    P->max = max;
    return (P);
}

void destroiPilha(Pilha P) {
    free(P);
}

int pertenceP(char beta[])
{
    int i, meio = 0;
    Pilha P = criaPilha(15);
    for (i = 0; beta[i] != '\0'; i++) {
        if (beta[i] == 'c') {
            meio = 1;
        } else if(meio == 0) {
            empilha(P, beta[i]);
        } else {
            if (topoDaPilha(P) != beta[i])
                return (0);
            desempilha(P);
        }
    }  
    destroiPilha(P);
    return (1);
}

void invertePalavras(char frase[])
{
    Pilha P = criaPilha(50);
    int i, ultima = 0;
    for (i = 0; frase[i] != '\0'; i++) {
        if (frase[i] != ' ' && frase[i] != '.') {
            empilha(P, frase[i]);
        } else {
            printf (" ");
            while (!pilhaVazia(P)) {
                printf("%c", topoDaPilha(P)); 
                desempilha(P);
            }
            if (frase[i] == '.') {
                printf("."); return;
            }
        }
    }
}

int operador(char op) {
    if (op != '+' && op != '-' && op != '*' && op != '/' && op != '^')
        return (0);
    return (1);
}

int precedencia(char op) {
    switch (op) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        case '(':
            return 0;
        default:
            return -1;
    }
}

void convertePosfixa(char expr[])
{
    Pilha P = criaPilha(100);
    int i;
    char c;
    for (i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') {
            empilha(P, expr[i]);
        } else if (expr[i] == ')') {
            c = topoDaPilha(P);
            while (c != '(') {
                printf("%c", c);
                desempilha(P); 
                c = topoDaPilha(P);
            }
            desempilha(P);
        } else if (operador(expr[i])) {
            if (pilhaVazia(P)) {
                empilha(P, expr[i]);
            } else {
                c = topoDaPilha(P);
                while (precedencia(c) >= precedencia(expr[i]) && !pilhaVazia(P)) {
                    printf("%c", c);
                    desempilha(P);
                    if (!pilhaVazia(P))
                        c = topoDaPilha(P);
                } 
                empilha(P, expr[i]);
            }
        } else if (expr[i] != ' ') {
            printf("%c", expr[i]);
        }    
    }
    while (!pilhaVazia(P)) {
        printf("%c", topoDaPilha(P));
        desempilha(P);
    }
    destroiPilha(P);
}




int main(int argc, char const *argv[])
{
    char b[] = "((A * (B + C) ) / D)";
    convertePrefixa(b, strlen(b));
    return (0);
}
