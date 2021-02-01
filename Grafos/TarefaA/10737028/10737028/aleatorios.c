// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Victor Pereira Lima
// Número USP: 10737028
// Tarefa:     A
// Data:       2019-08-08
//
// Solução baseada em ... <se for o caso> ...
//
// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. TODAS
// AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO PROFESSOR
// OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK OU ROBERTS,
// FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR
// TODAS AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM
// FACILITEI A DISTRIBUIÇÃO DE CÓPIAS. 
//
////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "GRAPHlists.h"


int
vertexGrauSaida(Graph G, vertex v)
{
    int grau = 0;
    for (link p = G->adj[v]; p != NULL; p = p->next) {
        grau++;
    }
    return (grau);
}

int
*GRAPHgrauSaida(Graph G)
{
    int *grauSaida = malloc (G->V * sizeof (int));
    for (int v = 0; v < G->V; v++) {
        grauSaida[v] = vertexGrauSaida(G, v);
    }
    return (grauSaida);
}

int
*GRAPHgrauEntrada(Graph G)
{
    int *grauEntrada = malloc (G->V * sizeof (int));
    for (vertex v = 0; v < G->V; ++v) {
      for (link a = G->adj[v]; a != NULL; a = a->next) {
          grauEntrada[a->w]++;
      }
   }
    return (grauEntrada);
}

int
frequenciaVertices(int *grau, int tam, int g)
{
    int freq = 0;
    for (int i = 0; i < tam; i++) {
        if (grau[i] == g)
            freq++;
    }
    return freq;
}

void
constroiTabela(Graph G, int *grau)
{
    int m = grau[0];
    for (int v = 1; v < G->V; v++) {
        if (grau[v] > m)
            m = grau[v];
    }
    for (int g = 0; g < 4; g++) {
        printf ("grau: %2d   frequencia de vertices: ", g);
            printf ("%d\n", frequenciaVertices(grau, G->V, g));
        printf ("grau: %2d   frequencia de vertices: ", m - g); 
            printf ("%d\n", frequenciaVertices(grau, G->V, m - g));
    }
}

void
GRAPHtestaConstrucaoAleatoria(Graph (*GRAPHrandN)(int, int), int V, int A)
{
    double inicio, final;
    inicio = (double) clock () / CLOCKS_PER_SEC;
    Graph G = GRAPHrandN(V, A);
    final = (double) clock () / CLOCKS_PER_SEC;
    printf ("O grafo construido aleatoriamente");
        printf ("possui %d vertices e %d arcos.\n", G->V, G->A);
    printf ("Tempo gasto : %lfs\n", final - inicio);
    printf ("Tabela com os graus de saida: \n");
    constroiTabela(G, GRAPHgrauSaida(G)); 
    printf("Tabela com os graus de entrada: \n");
    constroiTabela(G, GRAPHgrauEntrada(G));
    if (G->V < 30) {
        printf ("Lista de adjacencias do Grafo: \n");
        GRAPHshow(G);
    }
    GRAPHdestroy(G);
}

int main(int numargs, char *arg[])
{
    if (numargs != 3) {
        printf("Os argumentos foram passados de forma incorreta!\n");
        return (EXIT_FAILURE);
    }
    int V = strtol (arg[1], NULL, 10), A = strtol (arg[2], NULL, 10);
    printf ("\nTeste com GRAPHrand1: \n");
    GRAPHtestaConstrucaoAleatoria(GRAPHrand1, V, A);
    printf ("\nTeste com GRAPHrand2: \n");
    GRAPHtestaConstrucaoAleatoria(GRAPHrand2, V, A);
    return (EXIT_SUCCESS);
}