// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Victor Pereira Lima
// Número USP: 10737028
// Tarefa:     TarefaI
// Data:       2019-20-11
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

const int INFINITO = 10000000;

int
**copiaMatriz( int t, int f[t][t])
{
    int **m = mallocc(t * sizeof (int *));
    for (int i = 0; i < t; i++) {
        m[i] = mallocc(t * sizeof (int));
        for (int j = 0; j < t; j++) {
            m[i][j] = f[i][j];
        }
    }
    return (m);
}

int
maxFluxoPossivel(vertex s, int **f, int t)
{
    int max = 0;
    for (int i = 0; i < t; i++) {
        if (f[s][i] > max)
            max = f[s][i];
    }
    return (max);
}

bool
existeCaminhoComportaFluxo(Graph G, int **f, vertex s, vertex t, int fluxoDesejado)
{
    int *caminho;
    bool *visitado = mallocc( G->V * sizeof (bool));
    vertex v;
    int c = 1, cc;
    STACKinit( G->V);
    STACKpush(s);
    for (v = 0; v < G->V; v++)
        visitado[v] = false;
    visitado[s] = true;
    while (STACKempty() == false && STACKpeek() != t) {
        v = STACKpeek();
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            if (visitado[a->w] == false && f[v][a->w] >= fluxoDesejado) {
                STACKpush( a->w);
                visitado[a->w] = true;
                c += 1;
                break;
            }
        }
        if (STACKpeek() == v) {
            STACKpop();
            c -= 1;
        }
    }
    if (STACKempty()) {
        STACKfree();
        return (false);
    }
    cc = c;
    caminho = mallocc( c * sizeof (int));
    while (!STACKempty()) {
        v = STACKpop();
        caminho[--c] = v;
        if (v != s)
            f[STACKpeek()][v] -= fluxoDesejado;
    }
    printf("Caminho: ");
    for (c = 0; c < cc; c++)
        printf("%d-", caminho[c]);
    printf("\tFluxo: %d\n", fluxoDesejado);
    free( caminho); free( visitado);
    STACKfree();
    return (true);
}

void
macarronada( Graph G, vertex s, vertex t, int f[G->V][G->V])
{
    int **fDinamico = copiaMatriz( G->V, f);
    int fluxoPossivel = maxFluxoPossivel( s, fDinamico, G->V);
    while (fluxoPossivel > 0) {
        if (!existeCaminhoComportaFluxo( G, fDinamico, s, t, fluxoPossivel))
            fluxoPossivel -= 1;
        else
            fluxoPossivel = maxFluxoPossivel(s, fDinamico, G->V);
    }
    for (int i = 0; i < G->V; i++)
        free( fDinamico[i]);
    free( fDinamico);
}

void
dfsFluxo( Graph G, int *pa, int *cap, int *fluxoTotal, vertex s, vertex t, vertex v)
{
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        if (a->w != t) {
            pa[a->w] = v;
            cap[a->w] = a->cst;
            dfsFluxo( G, pa, cap, fluxoTotal, s, t, a->w);
        } else {
            int min = INFINITO;
            for (vertex w = v; w != s; w = pa[w]) 
                if (cap[w] < min)
                    min = cap[w];
            for (vertex w = v; w != s; w = pa[w]) 
                    cap[w] -= min;
            *fluxoTotal += min;
        }
    }
}

int
fluxoQuaseArvore( Graph G, vertex s, vertex t)
{
    int fluxo = 0;
    int *pa, *cap;
    pa = mallocc( G->V * sizeof (vertex));
    cap = mallocc( G->V * sizeof (int));
    for (vertex v = 0; v < G->V; v++) {
        pa[v] = v;
        cap[v] = 0;
    }
    pa[s] = -1;
    dfsFluxo( G, pa, cap, &fluxo, s, t, s);
    free( pa); free( cap);
    return (fluxo);
}

int
main( )
{
    srand( time( NULL));
    Graph G, Q;
    G = GRAPHinit( 6);
    GRAPHinsertArc( G, 0, 2); GRAPHinsertArc( G, 0, 3);
    GRAPHinsertArc( G, 2, 4); GRAPHinsertArc( G, 3, 4);
    GRAPHinsertArc( G, 4, 1); GRAPHinsertArc( G, 4, 5);
    GRAPHinsertArc( G, 5, 1);
    int f[6][6] = { {0, 0, 2, 4, 0, 0}, {0, 0, 0, 0, 0, 0}, 
                      {0, 0, 0, 0, 2, 0}, {0, 0, 0, 0, 4, 0}, 
                      {0, 3, 0, 0, 0, 3}, {0, 3, 0, 0, 0, 0}};
    macarronada( G, 0, 1, f);
    Q = GRAPHinit( 15);
    GRAPHinsertArc_c( Q, 4, 2, randInteger(10, 50)); 
    GRAPHinsertArc_c( Q, 4, 3, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 2, 13, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 2, 1, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 2, 7, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 1, 10, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 1, 9, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 3, 6, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 3, 0, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 6, 12, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 0, 11, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 0, 5, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 0, 8, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 7, 14, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 10, 14, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 8, 14, randInteger(10, 50));
    GRAPHinsertArc_c( Q, 13, 14, randInteger(10, 50));
    // GRAPHshow_c(Q);
    printf("\nFluxo na quase arvore: %d\n", fluxoQuaseArvore( Q, 4, 14));
}