// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Victor Pereira Lima
// Número USP: 10737028
// Tarefa:     TarefaE
// Data:       2019-12-09
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
UGRAPHeBiconexo( UGraph G)
{
    if (!UGRAPHisConnected( G))
        return (false);  
    for (vertex v = 0; v < G->V; v++) {
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            vertex w = a->w;
            UGRAPHremoveEdge( G, v, w);
            if (!GRAPHreach( G, v, w))
                return (false);
            UGRAPHinsertEdgeQuick( G, v, w);
        }
    }
    return (true);
}

int 
main()
{
    // srand( time);
    UGraph G = UGRAPHrand1( 8, 12);
    GRAPHshow( G);
    printf( "O grafo é biconexo?: %d\n", UGRAPHeBiconexo( G));
    GRAPHdestroy( G);
    return (0);
}