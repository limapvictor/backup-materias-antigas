// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      Victor Pereira Lima
// Número USP: 10737028
// Tarefa:     TarefaC
// Data:       2019-29-08
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

void
GRAPHimprimeCiclo( vertex *pa, vertex primeiro, vertex atual)
{
    if (primeiro != atual)
        GRAPHimprimeCiclo (pa, primeiro, pa[atual]);
    printf( "%d-", atual);
}

bool
CouT1( Graph G) 
{
    bool temCiclo = false;
    vertex v;
    int *pre = mallocc( G->V * sizeof (int));
    int *post = mallocc( G->V * sizeof (int));
    int *pa = mallocc( G->V * sizeof (vertex));
    GRAPHdfs( G, pre, post, pa);
    for (v = 0; v < G->V && !temCiclo; v++) {
        for (link a = G->adj[v]; a != NULL && !temCiclo; a = a->next) {
            vertex w = a->w;
            if (post[v] < post[w]) { // v-w é de retorno
                temCiclo = true;
                pa[w] = v--;
            }
        }
    }
    if (temCiclo) {
        printf( "O grafo possui o ciclo a seguir: \n");
        GRAPHimprimeCiclo ( pa, v, pa[v]);
        printf( "%d\n", v);
    } else {
        printf( "O grafo possui a numeração topologica a seguir: \n");
        for (int i = G->V - 1; i >= 0; i--) {
            for (v = 0; post[v] != i; v++);
            printf( "%d ", v);
        }
        printf( "\n");
    }
    free( post);
    free( pre);
    free( pa);
    return (temCiclo);
}

int cnt, cntt;

static int 
dfsCouT2( Graph G, vertex v, int *pre, int *post, vertex *pa) { 
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        if (pre[w] == -1) {
                pa[w] = v;
                int ind = dfsCouT2( G, w, pre, post, pa);
                if (ind != -1)
                    return (ind);
        } else {
                if (post[w] == -1) {
                    pa[w] = v;
                    return (w);
                }
        }
    }
    post[v] = cntt++;
    return (-1);
}

bool 
CouT2( Graph G) { 
    int *pre = mallocc( G->V * sizeof (int));
    int *post = mallocc( G->V * sizeof (int));
    int *pa = mallocc( G->V * sizeof (vertex));
    int indicadora = -1;
    vertex v;
    cnt = cntt = 0;
    for (v = 0; v < G->V; ++v)
        pre[v] = post[v] = -1;
    for (v = 0; v < G->V; ++v) {
        if (pre[v] == -1) {
            pa[v] = v;
            indicadora = dfsCouT2( G, v, pre, post, pa);
            if (indicadora != -1) break; // temos um ciclo
        }
    }
    if (indicadora != -1) {
        printf( "O grafo possui o ciclo a seguir: \n");
        GRAPHimprimeCiclo( pa, indicadora, pa[indicadora]);
        printf( "%d\n", indicadora);
    } else {
        printf( "O grafo possui a numeração topologica a seguir: \n");
        for (int i = G->V - 1; i >= 0; i--) {
            for (v = 0; post[v] != i; v++);
            printf( "%d ", v);
        }
        printf( "\n");
    }
    free( pa);
    free( post);
    free( pre);
    return (indicadora != -1);
}

bool imprimiu = false;

void
dfsCouT3( Graph G, vertex v, int *pa, bool *naPilha)
{
    naPilha[v] = true;
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        if (pa[a->w] == -1) {
            pa[a->w] = v;
            dfsCouT3( G, a->w, pa, naPilha);
        } else if (naPilha[a->w] && !imprimiu) {
            printf( "O grafo possui o ciclo a seguir: \n");
            vertex *pilhaAux = mallocc( G->V * sizeof (vertex));
            int ini = 0;
            for (vertex x = v; x != a->w; x = pa[x])
                pilhaAux[ini++] = x;
            pilhaAux[ini++] = a->w; pilhaAux[ini++] = v;
            for (int i = ini - 1; i >= 0; i--)
                printf( "%d-", pilhaAux[i]);
            printf( "\n");
            free( pilhaAux);
            imprimiu = true;
        }
    }
    naPilha[v] = false;
}


bool
CouT3( Graph G)
{   
    int *grauEntrada = mallocc( G->V * sizeof (int));
    int *topo = mallocc( G->V * sizeof (int));
    vertex v;
    int cont = 0;
    QUEUEinit( G->V);
    for (v = 0; v < G->V; v++) {
        grauEntrada[v] = GRAPHindeg( G, v);
        if (grauEntrada[v] == 0)
            QUEUEput( v);
    }
    while (!QUEUEempty()) {
        v = QUEUEget();
        topo[v] = cont++;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            grauEntrada[a->w] -= 1; 
            if (grauEntrada[a->w] == 0) 
                QUEUEput( a->w);
        }
    }
    QUEUEfree();
    if (cont < G->V) {
        vertex *pa = mallocc( G->V * sizeof (vertex));
        bool *naPilha = mallocc( G->V * sizeof (bool));
        for (v = 0; v < G->V; v++) {
            pa[v] = -1;
            naPilha[v] = false;
        }   
        for (v = 0; grauEntrada[v] == 0; v++);
        pa[v] = v;
        dfsCouT3( G, v, pa, naPilha);
        free( pa);
        free( naPilha);
    } else {
        printf( "O grafo possui a numeração topologica a seguir: \n");
        for (int i = G->V - 1; i >= 0; i--) {
            for (v = 0; topo[v] != i; v++);
            printf( "%d ", v);
        }
        printf( "\n");
    }
    free( grauEntrada);
    free( topo);
    return (cont >= G->V);
}


int 
main( int argc, char **argv)
{
    if (argc != 4) {
        printf( "Os argumentos foram passados de forma incorreta!");
        return (EXIT_FAILURE);
    }
    int V = strtol( argv[1], NULL, 10), A = strtol( argv[2], NULL, 10);
    int s = strtol( argv[3], NULL, 10); srand( s);
    Graph G = GRAPHrand2( V, A);
    double inicio, final;
    printf( "\nTestando o grafo com Cout1\n");
    inicio = (double) clock () / CLOCKS_PER_SEC;
    CouT1( G);
    final = (double) clock () / CLOCKS_PER_SEC;
    printf( "Tempo gasto na chamada de Cout1: %lfs\n", final - inicio);
    printf( "\nTestando o grafo com CouT2\n");
    inicio = (double) clock () / CLOCKS_PER_SEC;
    CouT2( G);
    final = (double) clock () / CLOCKS_PER_SEC;
    printf( "Tempo gasto na chamada de CouT2: %lfs\n", final - inicio);
    printf( "\nTestando o grafo com CouT3\n");
    inicio = (double) clock () / CLOCKS_PER_SEC;
    CouT3( G);
    final = (double) clock () / CLOCKS_PER_SEC;
    printf( "Tempo gasto na chamada de CouT3: %lfs\n", final - inicio);
    GRAPHdestroy( G);
    return (EXIT_SUCCESS);
}