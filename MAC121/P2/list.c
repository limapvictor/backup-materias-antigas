#include <stdio.h>
#include <stdlib.h>

struct celula {
    int info;
    struct celula *prox;
};
typedef struct celula *apontador;

struct item {
    float coef;
    int expo;
    struct item *prox;
};
typedef struct item *polinomio;

apontador insere(apontador inicio, int x)
{
    apontador p, novo;
    for (p = inicio; p != NULL && p->prox != NULL; p = p->prox);
    novo = malloc (sizeof (struct celula));
    novo->info = x; novo->prox = NULL;
    if (p == NULL) return (novo);
    p->prox = novo;
    return (inicio);
}

void printLista(apontador inicio)
{
    apontador p;
    for (p = inicio; p != NULL; p = p->prox) printf("%d ", p->info);
    printf("\n");
}

void removeRepetidos(apontador inicio)
{
    apontador p, aux;
    for (p = inicio; p != NULL && p->prox != NULL; p = p->prox) {
        if (p->info == p->prox->info) {
            aux = p->prox;
            p->prox = p->prox->prox;
            free (aux);
        }
    }
}

apontador inverteLista(apontador inicio)
{
    apontador p = inicio, aux, ant = NULL;
    while (p->prox != NULL) {
        aux = p;
        p = p->prox;
        aux->prox = ant;
        ant = aux;
    }
    p->prox = aux;
    return (p);
}

void parImpar(apontador inicio)
{
    apontador p = inicio, aux, par = NULL, impar = NULL, iniPar, iniImpar;
    while (p != NULL) {
        aux = p;
        p = p->prox;
        if (aux->info % 2 == 0) {
            if(par == NULL) {
                iniPar = aux;
                par = iniPar;
            } else {
                par->prox = aux;
                par = par->prox;
            } 
        } else {
            if(impar == NULL) {
                iniImpar = aux;
                impar = iniImpar;
            } else {
                impar->prox = aux;
                impar = impar->prox;
            } 
        }
    }
    impar->prox = NULL; par->prox = NULL;
    printLista(iniImpar); printLista(iniPar);
}

void circulariza(apontador inicio){
    apontador p;
    for (p = inicio; p->prox != NULL; p = p->prox);
    p->prox = inicio;
}

apontador inverte(apontador atual, apontador anterior)
{
    apontador inicio;
    if (atual->prox != NULL) {
        inicio = inverte(atual->prox, atual);
    } 
    atual->prox = anterior;
    return (inicio);
}

polinomio insereP(polinomio inicio, float coef, int expo)
{
    polinomio p, novo;
    for (p = inicio; p != NULL && p->prox != NULL; p = p->prox);
    novo = malloc (sizeof (struct item));
    novo->coef = coef; novo->expo = expo; novo->prox = NULL;
    if (p == NULL) return (novo);
    p->prox = novo;
    return (inicio);
}

void printPolinomio(polinomio inicio)
{
    polinomio p;
    for (p = inicio; p != NULL; p = p->prox) printf("%.2fx^%d ", p->coef, p->expo);
    printf("\n");
}

polinomio inverteP(polinomio atual, polinomio ant)
{
    polinomio inicio;
    if (atual->prox != NULL) {
        inicio = inverteP(atual->prox, atual);
    } else inicio = atual; 
    atual->prox = ant;
    return (inicio);
}

polinomio derivada(polinomio inicio)
{
    polinomio p, d = NULL;
    for (p = inicio; p != NULL; p = p->prox) {
        if (p->expo != 0) {
            d = insereP(d, p->coef * p->expo, p->expo - 1);
        }
    }
    return (d);
}

polinomio divide(polinomio inicio, int a)
{
    polinomio p = inicio, d = NULL;
    int i = p->expo - 1;
    float x = p->coef;
    d = insereP(d, x, i);
    p = p->prox;
    for (i; i > 0; i--) {
         x = x * a;
        if (p->expo == i) {
            x += p->coef;
            p = p->prox;
        }
        d = insereP(d, x, i);    
    }
    if (p->expo == 0) printf ("Resto = %.2f \n", x * a + p->coef);
    else printf("Resto = %.2f \n", x * a );
    return (d);
}

// apontador removeCircular(apontador inicio, int x)
// {
//     apontador p = inicio, lixo;
//     int volta = -1;
//     while (volta < 0 || p != inicio) {
//         if(p == inicio) volta++;
//         if (p->info == x) {
//             if (p == inicio) inicio = p->prox;
//             lixo = p;
//             p = p->prox;
//             free (lixo);
//         }

//     }
// }

int main()
{
    // apontador lista = NULL, a;
    // lista = insere(lista, 1); lista = insere(lista, 2); lista = insere(lista, 2); 
    // lista = insere(lista, 3); lista = insere(lista, 4); lista = insere(lista, 4);
    // lista = insere(lista, 5); lista = insere(lista, 6); lista = insere(lista, 7);
    // printLista(lista);
    // removeRepetidos(lista);
    // printLista(lista);
    // circulariza(lista);
    // lista = inverteLista(lista);
    // printLista(lista);
    // parImpar(lista);
    polinomio p = NULL, pDiv, pDer;
    p = insereP(p, 1.0, 0); p = insereP(p, +3.0, 2); p = insereP(p, -2.0, 4); p = insereP(p, +3.0, 5);
    printPolinomio(p);
    p = inverteP(p, NULL); printPolinomio(p);
    pDer = derivada(p); printPolinomio(pDer);
    pDiv = divide(p, 2); printPolinomio(pDiv);
}