#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "lista.h"
#include "arvore.h"

char *minimizaPalavra(char *palavra)
{ /*Função que deixa a string inteira em letras minúsculas*/
    int i;
    for (i = 0; palavra[i] != '\0'; i++) {
        if (palavra[i] >= 'A' && palavra[i] <= 'Z') { /*Para letras ASCII*/
            palavra[i] = palavra[i] + 32;
        } else if (palavra[i] < -98 && palavra[i] != -61) { /*Para letras UTF-8*/
            palavra[i] = palavra[i] + 32;
        }
    }
    return palavra;
}

int defineEstrutura(char estrutura[], char ordem[])
{
    if (strcmp (estrutura, "VD") == 0) {
        if (strcmp (ordem, "A") == 0) return 1;
        if (strcmp (ordem, "O") == 0) return 2;
    } 
    if (strcmp (estrutura, "VO") == 0) {
        if (strcmp (ordem, "A") == 0) return 3;
        if (strcmp (ordem, "O") == 0) return 4;
    } 
    if (strcmp (estrutura, "LD") == 0) {
        if (strcmp (ordem, "A") == 0) return 5;
        if (strcmp (ordem, "O") == 0) return 6;
    } 
    if (strcmp (estrutura, "LO") == 0) {
        if (strcmp (ordem, "A") == 0) return 7;
        if (strcmp (ordem, "O") == 0) return 8;
    } 
    if (strcmp (estrutura, "AB") == 0) {
        if (strcmp (ordem, "A") == 0) return 9;
        if (strcmp (ordem, "O") == 0) return 10;
    }
    return -1;
}

void migraArvoreVetor(no raiz, item *v, int *i)
{ /*Função que copia as informações do nó de uma árvore para uma posição do vetor*/
    if (raiz != NULL) {
        v[*i].palavra = raiz->palavra; 
        v[*i].cont = raiz->cont;
        *i += 1;
        migraArvoreVetor(raiz->esq, v, i);
        migraArvoreVetor(raiz->dir, v, i);
    }
}

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
    char *palavra, expressao[80], naoAlfa[] = ".,;:?!'\"()[]{}<>—-+*/\\=#&$@_«»“”";
    int tipoEstrutura, n = 15000, contador = 0;
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
        item *v; v = malloc (n * sizeof (item));
        vetor = v;
    }
    while (!feof (arquivo)) {
        if (fscanf (arquivo, "%s", expressao) == 1) {
            palavra = strtok (expressao, naoAlfa);
            while (palavra != NULL) {
                palavra = minimizaPalavra(palavra);
                switch (tipoEstrutura) {
                    case 1:
                    case 2:
                        contador = insereVetorDesordenado(vetor, &n, contador, palavra); break;
                    case 3:
                    case 4:
                        contador = insereVetorOrdenado(vetor, &n, contador, palavra); break;
                    case 5:
                    case 6:
                        inicio = insereListaDesordenada(inicio, palavra); break;
                    case 7: 
                    case 8:
                        inicio = insereListaOrdenada(inicio, palavra); break;
                    case 9:
                    case 10:
                        raiz = insereArvore(raiz, palavra, &contador); break;
                    default:
                        break;
                }
                palavra = strtok (NULL, naoAlfa);
            } 
        }
    }
    fclose (arquivo);
    if (tipoEstrutura >= 1 && tipoEstrutura <= 4) {
        if (tipoEstrutura == 1)
            quickSort(vetor, 0, contador, 'A');
        else if (tipoEstrutura == 2 || tipoEstrutura == 4)
            quickSort(vetor, 0, contador, 'O');
        imprimeVetorOrdenado(vetor, contador, tipoEstrutura);
    } else if (tipoEstrutura >= 5 && tipoEstrutura <= 8) {
        if (tipoEstrutura == 5)
            inicio = mergeSortLista(inicio, 'A');
        else if (tipoEstrutura != 7)
            inicio = mergeSortLista(inicio, 'O');
        imprimeListaOrdenada(inicio);
    } else {
        if (tipoEstrutura == 9) {
            imprimeInOrdem(raiz);
        } else {
            vetor = malloc (contador * sizeof (item)); int i = 0; 
            migraArvoreVetor(raiz, vetor, &i); 
            quickSort(vetor, 0, contador, 'O'); imprimeVetorOrdenado(vetor, contador, tipoEstrutura);
        }
        deletaArvore(raiz);
    }
    return (0);
}