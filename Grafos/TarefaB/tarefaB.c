// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Victor Pereira Lima
// Número USP: 10737028
// Tarefa:     TarefaB 
// Data:       2019-14-08
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

bool
VERTEXeSorvedouro( Graph G, vertex v, int numRemovidos, vertex vertices[])
{
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        int i;
        for (i = 0; i < numRemovidos && a->w != vertices[G->V - 1 - i]; i++);
        if (numRemovidos == i)
            return (false);
    }
    return (true);
}

vertex
*criaVetorVertices( int V)
{
    vertex *ve = malloc (V * sizeof (int));
    for (int i = 0; i < V; i++) {
        ve[i] = i; 
    }
    return (ve);
}

void
trocaVertices( vertex vertices[], vertex v, vertex w)
{
    vertex aux = vertices[w];
    vertices[w] = vertices[v];
    vertices[v] = aux;
}

bool
tperm( Graph G, vertex vv[])
{
    for (int i = 0; i < G->V; i++) {
        for (link a = G->adj[vv[i]]; a != NULL; a = a->next) {
            for (int j = 0; j < i; j++) {
                if (a->w == vv[j])
                    return (false);
            }
        }
    }
    return (true);
}

bool 
top( Graph Top)
{
    Graph antiTop = GRAPHreverse( Top);
    int cont = 0, *vertices = criaVetorVertices( antiTop->V);
    bool repete = true;
    while (repete) {        
        repete = false;
        for (int v = 0; v < antiTop->V - cont; v++) {
            if (VERTEXeSorvedouro( antiTop, vertices[v], cont, vertices)) {
                repete = true;
                trocaVertices( vertices, v, antiTop->V - 1 - cont);
                cont++;
            }
        }
    }
    if (cont == antiTop->V)
        return (true);
    return (false);
}
// Um grafo não vazio não possuir mais fontes implica 
// que em algum lugar dele existe um ciclo conectando os vértices,
// logo o grafo não é topológico (segundo por quê).

void
testaEX1( Graph Perm)
{
    GRAPHinsertArcQuick( Perm, 8, 7); GRAPHinsertArcQuick( Perm, 7, 6);
    GRAPHinsertArcQuick( Perm, 6, 4); GRAPHinsertArcQuick( Perm, 6, 9);
    GRAPHinsertArcQuick( Perm, 2, 3); GRAPHinsertArcQuick( Perm, 2, 0);
    GRAPHinsertArcQuick( Perm, 0, 6); GRAPHinsertArcQuick( Perm, 0, 1);
    GRAPHinsertArcQuick( Perm, 0, 5); GRAPHinsertArcQuick( Perm, 3, 5);
    GRAPHinsertArcQuick( Perm, 9, 10); GRAPHinsertArcQuick( Perm, 9, 11);
    GRAPHinsertArcQuick( Perm, 11, 12); GRAPHinsertArcQuick( Perm, 9, 12);
    GRAPHinsertArcQuick( Perm, 5, 4);
    vertex vv[] = {8, 7,  2,  3,  0,  6,  9, 10, 11, 12,  1,  5,  4};
    printf ("A permutação vv é topologica? %d\n", tperm( Perm, vv));
    vv[0] = 6; vv[5] = 8;
    printf ("A permutação vv continua topologica? %d\n", tperm( Perm, vv));
}   
int 
main()
{
    Graph G = GRAPHinit( 13);
    testaEX1( G);
    printf ("O grafo é topológico? %d\n", top( G));
    GRAPHinsertArcQuick( G, 4, 2);
    printf ("O grafo continua topológico? %d\n", top( G));
    return (EXIT_SUCCESS);
}


// Exercicío 3
// 7 dfsR(G, 7)
//   7-5 dfsR(G, 5)    
//      5-4 dfsR(G, 4)
//          4
//      5-1 dfsR(G, 1)
//          1-3 dfsR(G, 3)
//              3-6 dfsR(G, 6)
//                  6-2 dfsR(G, 2)
//                      2
//                  6-0 dfsR(G, 0)
//                      0
//                  6
//              3
//          1
//      5
//  7
// pre[v] = {7, 3, 6, 4, 2, 1, 5, 0}
// pa[v] = {6, 5, 6, 1, 5, 7, 3, 7}