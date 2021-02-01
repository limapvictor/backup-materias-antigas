#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void troca(int *v, int i, int j)
{
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int separa(int *v, int ini, int fim)
{
    int pivo = v[fim - 1], i = ini - 1, j;
    for (j = ini; j < fim; j++) {
        if (v[j] <= pivo) {
            i++;
            troca(v, i, j);
        } 
    }
    return (i);
}

void quickSort(int *v, int ini, int fim)
{
    int pivo;
    if (fim - ini >= 2) {
        pivo = separa(v, ini, fim);
        quickSort(v, ini, pivo);
        quickSort(v, pivo + 1, fim);
    }
}

int buscaBin(int *v, int ini, int fim, int x)
{
    if (ini > fim) return (-1);
    int meio = (ini + fim) / 2;
    if (v[meio] == x) return meio;
    else if (v[meio] > x) return buscaBin(v, ini, meio, x);
    else return buscaBin(v, meio + 1, fim, x);
}

int buscaBinaria(int *v, int contador, int x)
{
    int ini = 0, fim = contador - 1, meio, comp;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        if (v[meio] == x){
            return (meio);
        } else if (v[meio] < x ) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return (-1);
}

int main(int agrc, char *argv[])
{
    // setlocale(LC_COLLATE, "");
    // char linha[200], palavra[60], *p;
    // char c;
    // int i;
    // FILE *arquivo;
    // arquivo = fopen("ep4.txt", "r");
    // if (arquivo == NULL) {
    //     perror("Erro ao abrir o arquivo: ");
    //     return (-1);
    // }
    // printf ("%d ", strcoll ("arroz", tolower("ARROZ"));
    // fclose(arquivo);
    // setlocale(LC_COLLATE, NULL);
    int v[] = {1,2,3,4,5,6};
    char b[] = "Os dois,juntos", *a;
    char s[] = "\"\\.,;:?!'()[]{}<>-+*/=_«»";
    a = strtok(b, s);
    printf("%s",a);
    while (a != NULL){
        a = strtok(NULL, s);
        printf("%s",a);
    }
    printf("%d", buscaBinaria(v, 6, 7));
}
// apontador criaLista()
// {
//     apontador p;
//     p = malloc (sizeof (struct celula));
//     p->palavra = NULL; p->prox = NULL;
//     return (p);
// }

// void insereListaOrdenadaAlfa(apontador lista, char *palavra)
// {
//     apontador p, ant, novo; 
//     for (ant = lista, p = lista->prox; p != NULL && comparaStrings(p->palavra, palavra) == -1; ant = p, p = p->prox);
//     if (p != NULL && comparaStrings(p->palavra, palavra) == 0) {
//         p->cont += 1;
//     } else {
//         novo = malloc (sizeof (struct celula));
//         novo->palavra = malloc ((tamPalavra(palavra) + 1) * sizeof (char)); copiaPalavra(palavra, novo->palavra);
//         novo->cont = 1;
//         novo->prox = p;
//         ant->prox = novo;
//     }
// }

// void insereListaDesordenada(apontador lista, char *palavra) 
// {
//     apontador p, novo;
//     for (p = lista; p->prox != NULL && comparaStrings(p->palavra, palavra) != 0; p = p->prox);
//     if (comparaStrings(p->palavra, palavra) == 0) {
//         p->cont += 1;
//     } else {
//         novo = malloc (sizeof (struct celula));
//         novo->palavra = malloc ((tamPalavra(palavra) + 1) * sizeof (char)); copiaPalavra(palavra, novo->palavra);
//         novo->cont = 1;
//         novo->prox = p->prox;
//         p->prox = novo;
//     }
// }


// int tamPalavra(char *palavra)
// {
//     int i;
//     for (i = 0; palavra[i] != '\0'; i++);
//     return (i);
// }

// int comparaStrings(char *a, char *b)
// { /* Retorna -1 se a < b; 0 se a = b e 1 se a > b */
//     if (a == NULL || b == NULL) return (-1);
//     int i;
//     for (i = 0; a[i] != '\0' && b[i] != '\0' && a[i] == b[i]; i++);
//     if (a[i] < b[i]) return (-1);
//     if (a[i] > b[i]) return (1);
//     return (0);
// }

// void copiaPalavra(char *origem, char *destino)
// {
//     int i;
//     for (i = 0; origem[i] != '\0'; i++) {
//         destino[i] = origem[i];
//     }
//     destino[i] = '\0';
// }

// char s[] = "Essa!? é, uma frase normal.\tTeste?ola normal \n. guarda-chuva! - ola";
    // char *v;
    // v = strtok (s," ,.?!");
    // while (v != NULL) {
    //     if (strcmp(v, "-") != 0) printf ("%s %d \n",v, strlen(v));
    //     v = strtok (NULL, " \t\n,.?!1234567890");
    // }

    // ini = insereListaDesordenada(ini, "ola"); ini = insereListaDesordenada(ini, "caraio"); ini = insereListaDesordenada(ini, "ola");
    // ini = insereListaDesordenada(ini, "bola"); ini = insereListaDesordenada(ini, "ole"); ini = insereListaDesordenada(ini, "caraio");
    // ini = insereListaDesordenada(ini, "caraio"); ini = insereListaDesordenada(ini, "abacate"); ini = insereListaDesordenada(ini, "ole");

    // inicio = insereListaOrdenadaAlfa(inicio, "ola"); inicio = insereListaOrdenadaAlfa(inicio, "caraio"); inicio = insereListaOrdenadaAlfa(inicio, "ola");
    // inicio = insereListaOrdenadaAlfa(inicio, "bola"); inicio = insereListaOrdenadaAlfa(inicio, "ole"); inicio = insereListaOrdenadaAlfa(inicio, "caraio");
    // inicio = insereListaOrdenadaAlfa(inicio, "caraio"); inicio = insereListaOrdenadaAlfa(inicio, "abacate"); inicio = insereListaOrdenadaAlfa(inicio, "ole");

    // inic = insereListaOrdenadaOcorre(inic, "ola"); inic = insereListaOrdenadaOcorre(inic, "caraio"); inic = insereListaOrdenadaOcorre(inic, "ola");
    // inic = insereListaOrdenadaOcorre(inic, "bola"); inic = insereListaOrdenadaOcorre(inic, "ole"); inic = insereListaOrdenadaOcorre(inic, "caraio");
    // inic = insereListaOrdenadaOcorre(inic, "caraio"); inic = insereListaOrdenadaOcorre(inic, "abacate"); inic = insereListaOrdenadaOcorre(inic, "ole");
    
    // raiz = insereArvore(raiz, "ola"); raiz = insereArvore(raiz, "caraio"); raiz = insereArvore(raiz, "ola");
    // raiz = insereArvore(raiz, "bola"); raiz = insereArvore(raiz, "ole"); raiz = insereArvore(raiz, "caraio");
    // raiz = insereArvore(raiz, "caraio"); raiz = insereArvore(raiz, "abacate"); raiz = insereArvore(raiz, "ole");

// while(c != EOF) {
    //     // printf("%c",c);
    //     // c = fgetc(arquivo);
    //     for (i = 0; i < 200; i++) linha[i] = '\0';
    //     i = 0;
    //     while (c != '\n') {
    //         linha[i++] = c;
    //         c = fgetc(arquivo);
    //     }
    //     printf("%s %d \n", linha, i);
    //     c = fgetc(arquivo);
    // } 

    
// apontador insereListaOrdenadaOcorre(apontador inicio, char *palavra)
// {
//     apontador novo;
//     if (inicio == NULL) {
//         novo = malloc (sizeof (struct celula));
//         novo->palavra = malloc ((strlen (palavra) + 1) * sizeof (char)); strcpy (novo->palavra, palavra);
//         novo->cont = 1;
//         novo->prox = NULL;
//         return (novo);
//     }
//     if (strcoll (inicio->palavra, palavra) == 0) {
//         inicio->cont += 1;
//         return (inicio);
//     }
//     novo = insereListaOrdenadaOcorre(inicio->prox, palavra);
//     if (novo->cont > inicio->cont) {
//         inicio->prox = novo->prox;
//         novo->prox = inicio;
//         return (novo);
//     }
//     inicio->prox = novo;
//     return (inicio);
// }