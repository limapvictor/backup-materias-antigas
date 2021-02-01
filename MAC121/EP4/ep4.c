#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct celula {
    char *palavra;
    int cont;
    struct celula *prox;
};
typedef struct celula *apontador;

struct registro {
    char *palavra;
    int cont;
    struct registro *esq;
    struct registro *dir;
    struct registro *pai;
};
typedef struct registro *no;

typedef struct {
    char *palavra;
    int cont;
} item;

char *minimizaPalavra(char *palavra)
{
    int i;
    for (i = 0; palavra[i] != '\0'; i++) {
        if (palavra[i] >= 'A' && palavra[i] <= 'Z') {
            palavra[i] = palavra[i] + 32;
        } else if (palavra[i] < -98 && palavra[i] != -61) {
            palavra[i] = palavra[i] + 32;
        }
    }
    return palavra;
}

int defineEstrutura(char estrutura[], char ordem[])
{
    if (strcmp(estrutura, "VD") == 0) {
        if (strcmp(ordem, "A") == 0) return 1;
        if (strcmp(ordem, "O") == 0) return 2;
    } 
    if (strcmp(estrutura, "VO") == 0) {
        if (strcmp(ordem, "A") == 0) return 3;
        if (strcmp(ordem, "O") == 0) return 4;
    } 
    if (strcmp(estrutura, "LD") == 0) {
        if (strcmp(ordem, "A") == 0) return 5;
        if (strcmp(ordem, "O") == 0) return 6;
    } 
    if (strcmp(estrutura, "LO") == 0) {
        if (strcmp(ordem, "A") == 0) return 7;
        if (strcmp(ordem, "O") == 0) return 8;
    } 
    if (strcmp(estrutura, "AB") == 0) {
        if (strcmp(ordem, "A") == 0) return 9;
        if (strcmp(ordem, "O") == 0) return 10;
    }
    return -1;
}

//Implementação com VETORES//
int insereVetorDesordenado(item *vetor, int *n, int contador, char *palavra)
{
    if (contador == *n - 1) {
        *n += 1000;
        vetor = realloc (vetor, *n);
    }
    int i;
    for (i = 0; i < contador && strcoll(palavra, vetor[i].palavra) != 0; i++);
    if (i != contador && strcoll(palavra, vetor[i].palavra) == 0) {
        vetor[i].cont += 1;
        return (contador);
    } else {
        vetor[i].palavra = malloc ((strlen (palavra) + 1) * sizeof (char)); strcpy(vetor[i].palavra, palavra);
        vetor[i].cont = 1;
        return (contador + 1);
    }
}

void buscaVetorDesordenado(item *vetor, int contador)
{
    int i;
    for (i = 0; i < contador; i++) {
        printf ("%s %d \n", vetor[i].palavra, vetor[i].cont);
    }
}

int insereVetorOrdenenadoAlfa(item *vetor, int *n, int contador, char *palavra)
{
    if (contador == *n - 1) {
        *n += 1000;
        vetor = realloc (vetor, *n);
    }
    int i, j;
    for (i = 0; i < contador && strcoll(palavra, vetor[i].palavra) > 0; i++);
    if (i != contador && strcoll(palavra, vetor[i].palavra) == 0) {
        vetor[i].cont += 1;
        return (contador);
    } else {
        for (j = contador; j > i; j--) {
            vetor[j] = vetor[j - 1];
        }
        vetor[i].palavra = malloc ((strlen (palavra) + 1) * sizeof (char)); strcpy(vetor[i].palavra, palavra);
        vetor[i].cont = 1;
        return (contador + 1);
    }
}

void buscaVetorOrdenado(item *vetor, int contador)
{
    int i;
    for (i = 0; i < contador; i++) {
        printf ("%s %d \n", vetor[i].palavra, vetor[i].cont);
        free (vetor[i].palavra);
    }
    free (vetor);
}

//Fim implementação com VETORES//

//Implementação com LISTAS LIGADAS//
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

apontador insereListaOrdenadaAlfa(apontador inicio, char *palavra)
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
        inicio->prox = insereListaOrdenadaAlfa(inicio->prox, palavra);
        return (inicio);
    }
}

apontador insereListaOrdenadaOcorre(apontador inicio, char *palavra)
{
    apontador novo, aux;
    if (inicio == NULL) {
        novo = malloc (sizeof (struct celula));
        novo->palavra = malloc ((strlen (palavra) + 1) * sizeof (char)); strcpy (novo->palavra, palavra);
        novo->cont = 1;
        novo->prox = NULL;
        return (novo);
    }
    if (strcoll (inicio->palavra, palavra) == 0) {
        inicio->cont += 1;
        return (inicio);
    }
    novo = insereListaOrdenadaOcorre(inicio->prox, palavra);
    if (novo->cont > inicio->cont) {
        inicio->prox = novo->prox;
        novo->prox = inicio;
        return (novo);
    }
    inicio->prox = novo;
    return (inicio);
}

void buscaRemoveListaOrdenada(apontador inicio)
{
    apontador p = inicio, aux;
    while (p != NULL) {
        printf ("%s %d \n", p->palavra, p->cont);
        aux = p;
        p = p->prox;
        free (aux);
    }
}
/*Fim implementação com LISTAS LIGADAS*/

/*Implementação com ÁRVORES BINÁRIAS DE BUSCA*/
no insereArvore(no raiz, char *palavra)
{
    if (raiz == NULL) {
        raiz = malloc (sizeof (struct registro));
        raiz->palavra = malloc ((strlen (palavra) + 1) * sizeof (char)); strcpy (raiz->palavra, palavra);
        raiz->cont = 1;
        raiz->esq = NULL; raiz->dir = NULL; 
        return (raiz);
    }
    if (strcoll (raiz->palavra, palavra) == 0) {
        raiz->cont += 1;
    } else if (strcoll (raiz->palavra, palavra) > 0) {
        raiz->esq = insereArvore(raiz->esq, palavra);
    } else {
        raiz->dir = insereArvore(raiz->dir, palavra);
    }
    return (raiz);
}

void buscaInOrdem(no raiz)
{
    if (raiz != NULL) {
        buscaInOrdem(raiz->esq);
        printf ("%s %d\n", raiz->palavra, raiz->cont);
        buscaInOrdem(raiz->dir);
    }
}
/*Fim implementação com ÁRVORES BINÁRIAS DE BUSCA*/

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf ("Os argumentos da linha de comando não foram passados corretamente.");
        return (-1);
    } 
    FILE *arquivo;
    apontador inicio = NULL;
    no raiz = NULL;
    item *vetor;
    char *palavra, expressao[60];
    int tipoEstrutura, n = 1000, contador = 0;
    arquivo = fopen (argv[1], "r");
    if (arquivo == NULL) {
        perror ("Erro ao abrir o arquivo: ");
        return (-1);
    }
    tipoEstrutura = defineEstrutura(argv[2], argv[3]);
    if (tipoEstrutura == -1) {
        printf ("Os argumentos da linha de comando não foram passados corretamente.");
        return (-1);
    } else if (tipoEstrutura >= 1 && tipoEstrutura <= 4) {
        item *v; v = malloc (1000 * sizeof (item));
        vetor = v;
        vetor[0].cont = 1; vetor[0].palavra = "ola";
    }
    while (!feof (arquivo)) {
        if (fscanf (arquivo, "%s", expressao) == 1) {
            palavra = minimizaPalavra(strtok (expressao, ".,;!?:0123456789()"));
            // printf("%d -> %s\n", strlen(palavra), palavra); 
            switch (tipoEstrutura) {
                case 1:
                case 2:
                    contador = insereVetorDesordenado(vetor, &n, contador, palavra); break;
                case 3:
                    contador = insereVetorOrdenenadoAlfa(vetor, &n, contador, palavra); break;
                case 4:
                    contador = insereVetorOrdenenadoOcorre(vetor, &n, contador, palavra); break; 
                case 5:
                case 6:
                    inicio = insereListaDesordenada(inicio, palavra); break;
                case 7: 
                    inicio = insereListaOrdenadaAlfa(inicio, palavra); break;
                case 8: 
                    inicio = insereListaOrdenadaOcorre(inicio, palavra); break;
                case 9:
                    raiz = insereArvore(raiz, palavra); break;
                default:
                    break;
            }
        }
    }
    fclose (arquivo);
    switch (tipoEstrutura) {
        case 1:
        case 2:
            buscaVetorDesordenado(vetor, contador); break;
        case 3:
        case 4:
            buscaVetorOrdenado(vetor, contador); break;
        case 5:
        case 6:
            break;
        case 7: 
        case 8: 
            buscaRemoveListaOrdenada(inicio); break;
        case 9:
            buscaInOrdem(raiz); break;
        default:
            break;
    }
}

