// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Victor Pereira Lima
// Número USP: 10737028
// Tarefa:     TarefaH
// Data:       2019-30-10
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
#include "GRAPHlists.h"

int 
alturaRec( Graph T, vertex r)
{
    int altura, max = 0;
    for (link a = T->adj[r]; a != NULL; a = a->next) {
        altura = alturaRec( T, a->w);
        if (max < 1 + altura)
            max = 1 + altura;
    } 
    return (max);
}

int
altura( Graph T, vertex r)
{
    return alturaRec( T, r);
}

int 
emparelhamentoMaximal( UGraph G)
{
    int tamanho = 0;
    int *match = mallocc( G->V * sizeof (int));
    for (vertex v = 0; v < G->V; v++)
        match[v] = -1;
    for (vertex v = 0; v < G->V && tamanho < G->V / 2; v++) {
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            if (match[v] == -1 && match[a->w] == -1) {
                match[v] = a->w; match[a->w] = v;
                tamanho += 1;
                break;
            }
        }
    }
    for (vertex v = 0; v < G->V; v++)
        printf( "match[%d] = %d\t", v, match[v]);
    return (tamanho);
}

int 
main(void)
{
    Graph T = GRAPHinit( 6);
    GRAPHinsertArc( T, 4, 5);  GRAPHinsertArc( T, 5, 0);
    GRAPHinsertArc( T, 5, 1);  GRAPHinsertArc( T, 0, 2);
    GRAPHinsertArc( T, 0, 3);
    printf( "altura : %d\n", altura( T, 4));
    UGraph G = UGRAPHinit( 6);
    UGRAPHinsertEdge( G, 0, 5); UGRAPHinsertEdge( G, 0, 2);
    UGRAPHinsertEdge( G, 2, 1); UGRAPHinsertEdge( G, 3, 0);
    UGRAPHinsertEdge( G, 4, 0); UGRAPHinsertEdge( G, 0, 1); 
    printf( "\nnum emparelhamentos : %d\n", emparelhamentoMaximal( G));
}

// O conjunto X são todos os vértices vistos 
// na procura de um caminho aumentador, ou seja, 
// o conjunto de todos os vertices 
// que são términos de um caminho alternante. 
// 1.Conjunto X vazio => Para o conjunto X ser vazio, a fila dos 
// vértices solteiros de cor 0 deve estar vazia. Por exemplo, podemos
// ter um grafo "roda de carro" com um vértice de cor 0 no centro
// e vários outros ligados somente a esse vértice, recebendo assim a cor 1.
// Portanto iremos casar esse vértice na primeira iteração e já na segunda
// iteração não haverá mais nenhum vértice de cor 0 solteiro, sendo assim
// X estará vazio.
// 2. Conjunto X com todos vértices => Para o conjunto X possuir todos vértices, todos
// os vértices devem estar na fila. Isso vai ocorrer caso tenhamos um grafo sem arestas, 
// pois assim todos os vértices terão a cor 0 e estarão solteiros, logo irão entrar na fila.