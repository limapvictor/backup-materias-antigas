/****************************************************************
    Nome:   Victor Pereira Lima
    NUSP:   10737028

    Ao preencher esse cabeçalho com o meu nome e o meu número USP,
    declaro que todas as partes originais desse exercício programa (EP)
    foram desenvolvidas e implementadas por mim e que portanto não 
    constituem desonestidade acadêmica ou plágio.
    Declaro também que sou responsável por todas as cópias desse
    programa e que não distribui ou facilitei a sua distribuição.
    Estou ciente que os casos de plágio e desonestidade acadêmica
    serão tratados segundo os critérios divulgados na página da 
    disciplina.
    Entendo que EPs sem assinatura devem receber nota zero e, ainda
    assim, poderão ser punidos por desonestidade acadêmica.

    Abaixo descreva qualquer ajuda que você recebeu para fazer este
    EP.  Inclua qualquer ajuda recebida por pessoas (inclusive
    monitoras e colegas). Com exceção de material de MAC0323, caso
    você tenha utilizado alguma informação, trecho de código,...
    indique esse fato abaixo para que o seu programa não seja
    considerado plágio ou irregular.

    Exemplo:

        A monitora me explicou que eu devia utilizar a função xyz().

        O meu método xyz() foi baseada na descrição encontrada na 
        página https://www.ime.usp.br/~pf/algoritmos/aulas/enumeracao.html.

    Descrição de ajuda ou indicação de fonte:

    A resolução da inverseTransform() foi realizada basicamente em cima da ideia da KeyIndexed Sorting vista em 
    https://www.youtube.com/watch?v=S3HjlVv6x7Y&list=PLeipq3NgyTAl20PEUKBXMsoOCE6Q_vkp1&index=80

    Se for o caso, descreva a seguir 'bugs' e limitações do seu programa:
    A transform() demora bastante(em torno de 5min no meu PC) em textos grandes como o dickens.txt.

****************************************************************/
/*
 * MAC0323 Algoritmos e Estruturas de Dados II
 * 
 * ADT Topological é uma "representação topológica" de digrafo.
 * Esta implementação usa ADT Digraph do EP13.
 *  
 * Busque inspiração em: 
 *
 *   https://algs4.cs.princeton.edu/42digraph/
 *   https://algs4.cs.princeton.edu/42digraph/DepthFirstOrder.java
 *   https://algs4.cs.princeton.edu/42digraph/Topological.java
 *   https://algs4.cs.princeton.edu/42digraph/DirectedCycle.java
 * 
 * TOPOLOGICAL
 *
 * Topological é uma ¨representação topológica" de um dado digrafo.
 * 
 * As principais operações são: 
 *
 *      - hasCycle(): indica se o digrafo tem um ciclo (DirectedCycle.java)
 *      - isDag(): indica se o digrafo é acyclico (Topological.java)
 *
 *      - pre(): retorna a numeração pré-ordem de um vértice em relação a uma dfs 
 *               (DepthFirstOrder.java)
 *      - pos(): retorna a numareção pós-ordem de um vértice em relação a uma dfs
 *               (DepthFirstOrder.java)
 *      - rank(): retorna a numeração topológica de um vértice (Topological.java)
 * 
 *      - preorder(): itera sobre todos os vértices do digrafo em pré-ordem
 *                    (em relação a uma dfs, DepthFirstOrder.java)
 *      - postorder(): itera sobre todos os vértices do digrafo em pós-ordem
 *                    (em relação a uma dfs, ordenação topologica reversa, 
 *                     DepthFirstOrder.java)
 *      - order(): itera sobre todos os vértices do digrafo em ordem  
 *                 topologica (Topological.java)
 *      - cycle(): itera sobre os vértices de um ciclo (DirectedCycle.java)
 *
 * O construtor e "destrutor" da classe consomem tempo linear..
 *
 * Cada chama das demais operações consome tempo constante.
 *
 * O espaço gasto por esta ADT é proporcional ao número de vértices V do digrafo.
 * 
 * Para documentação adicional, ver 
 * https://algs4.cs.princeton.edu/42digraph, Seção 4.2 de
 * Algorithms, 4th Edition por Robert Sedgewick e Kevin Wayne.
 *
 */

/* interface para o uso da funcao deste módulo */
#include "topological.h"

#include "digraph.h" /* Digraph, vDigraph(), eDigraph(), adj(), ... */
#include "bag.h"     /* add() e itens() */
#include "util.h"    /* emalloc(), ecalloc(), ERRO(), AVISO() */

#include <stdlib.h>  /* free() */

#undef DEBUG
#ifdef DEBUG
#include <stdio.h>   /* printf(): para debugging */
#endif

/*----------------------------------------------------------*/
/* 
 * Estrutura básica de um Topological
 * 
 */
struct topological 
{
    Bool *marked, *onStack;
    int *pre, *post;
    vertex *preOrder, *postOrder;
    int V, preCounter, postCounter, orderCycleCounter, cycleLen;
    int *edgeTo;
    int *cycle, *rank, *order;
};

/*------------------------------------------------------------*/
/* 
 * Protótipos de funções administrativas: tem modificador 'static'
 * 
 */
static 
void dfs(Topological ts, Digraph G, vertex v);

Bool
isDag(Topological ts);

/*-----------------------------------------------------------*/
/*
 *  newTopologica(G)
 *
 *  RECEBE um digrafo G.
 *  RETORNA uma representação topológica de G.
 * 
 */
Topological
newTopological(Digraph G)
{
    int V = vDigraph(G), v, i = 0;
    Topological ts = emalloc (sizeof (struct topological));
    ts->marked = ecalloc (V, sizeof (int));
    ts->onStack = ecalloc (V, sizeof (int));
    ts->V = V;
    ts->pre = emalloc(V * sizeof(int)); ts->post = emalloc(V * sizeof(int));
    ts->preOrder = emalloc(V * sizeof(int)); ts->postOrder = emalloc(V * sizeof(int));
    ts->preCounter = 0; ts->postCounter = 0; ts->orderCycleCounter = 0;
    ts->edgeTo = emalloc(V * sizeof(int));
    ts->cycle = NULL; ts->rank = NULL; ts->order = NULL; 
    for (v = 0; v < V; v++) {
        if (!ts->marked[v])
            dfs(ts, G, v);
    }
    if (!hasCycle(ts)) {
        ts->rank = emalloc (V * sizeof (int));
        ts->order = emalloc (V * sizeof (int));
        for (v = 0; v < V; v++) {
            ts->order[v] = ts->postOrder[V - 1 - v];
        }
        for (v = 0; v < V; v++, i++)
            ts->rank[ts->order[v]] = i;
    }    
    return (ts);
}

/*-----------------------------------------------------------*/
/*
 *  freeTopological(TS)
 *
 *  RECEBE uma representação topologica TS.
 *  DEVOLVE ao sistema toda a memória usada por TS.
 *
 */
void  
freeTopological(Topological ts)
{
    if (isDag(ts)) {
        free (ts->rank); free (ts->order);
    } else {
        free (ts->cycle);
    }
    free (ts->marked); free (ts->onStack); free (ts->edgeTo);
    free (ts->pre); free (ts->post);
    free (ts->preOrder); free (ts->postOrder);
    free (ts);
}    

/*------------------------------------------------------------*/
/*
 *  OPERAÇÕES: 
 *
 */

/*-----------------------------------------------------------*/
/* 
 *  HASCYCLE(TS)
 *
 *  RECEBE uma representação topológica TS de um digrafo;
 *  RETORNA TRUE seu o digrafo possui um ciclo e FALSE em caso 
 *  contrário.
 *
 */
Bool
hasCycle(Topological ts)
{
    return (ts->cycle != NULL);
}

/*-----------------------------------------------------------*/
/* 
 *  ISDAG(TS)
 *
 *  RECEBE um representação topológica TS de um digrafo.
 *  RETORNA TRUE se o digrafo for um DAG e FALSE em caso 
 *  contrário.
 *
 */
Bool
isDag(Topological ts)
{
    return (ts->cycle == NULL);
}

/*-----------------------------------------------------------*/
/* 
 *  PRE(TS, V)
 *
 *  RECEBE uma representação topológica TS de um digrafo e um 
 *  vértice V.
 *  RETORNA a numeração pré-ordem de V em TS.
 *
 */
int
pre(Topological ts, vertex v)
{
    return (ts->pre[v]);
}

/*-----------------------------------------------------------*/
/* 
 *  POST(TS, V)
 *
 *  RECEBE uma representação topológica TS de um digrafo e um 
 *  vértice V.
 *  RETORNA a numeração pós-ordem de V em TS.
 *
 */
int
post(Topological ts, vertex v)
{
    return (ts->post[v]);
}

/*-----------------------------------------------------------*/
/* 
 *  RANK(TS, V)
 *
 *  RECEBE uma representação topológica TS de um digrafo e um 
 *  vértice V.
 *  RETORNA a posição de V na ordenação topológica em TS;
 *  retorna -1 se o digrafo não for um DAG.
 *
 */
int
rank(Topological ts, vertex v)
{
    if (!isDag(ts))
        return (-1);
    return (ts->rank[v]);
}

/*-----------------------------------------------------------*/
/* 
 *  PREORDER(TS, INIT)
 * 
 *  RECEBE uma representação topológica TS de um digrafo e um 
 *  Bool INIT.
 *
 *  Se INIT é TRUE,  PREORDER() RETORNA o primeiro vértice na ordenação pré-ordem de TS.
 *  Se INIT é FALSE, PREORDER() RETORNA o vértice sucessor do último vértice retornado
 *                   na ordenação pré-ordem de TS; se todos os vértices já foram retornados, 
 *                   a função retorna -1.
 */
vertex
preorder(Topological ts, Bool init)
{
    if (init) 
        ts->preCounter = 0;
    if (ts->preCounter == ts->V)
        return (-1);
    return (ts->preOrder[ts->preCounter++]);
}

/*-----------------------------------------------------------*/
/* 
 *  POSTORDER(TS, INIT)
 * 
 *  RECEBE uma representação topológica TS de um digrafo e um 
 *  Bool INIT.
 *
 *  Se INIT é TRUE,  POSTORDER() RETORNA o primeiro vértice na ordenação pós-ordem de TS.
 *  Se INIT é FALSE, POSTORDER() RETORNA o vértice sucessor do último vértice retornado
 *                   na ordenação pós-ordem de TS; se todos os vértices já foram retornados, 
 *                   a função retorna -1.
 */
vertex
postorder(Topological ts, Bool init)
{
    
   if (init) 
        ts->postCounter = 0;
    if (ts->postCounter == ts->V)
        return (-1);
    return (ts->postOrder[ts->postCounter++]);
}

/*-----------------------------------------------------------*/
/* 
 *  ORDER(TS, INIT)
 * 
 *  RECEBE uma representação topológica TS de um digrafo e um Bool INIT.
 *
 *  Se INIT é TRUE,  ORDER() RETORNA o primeiro vértice na ordenação topológica 
 *                   de TS.
 *  Se INIT é FALSE, ORDER() RETORNA o vértice sucessor do último vértice retornado
 *                   na ordenação topológica de TS; se todos os vértices já foram 
 *                   retornados, a função retorna -1.
 *
 *  Se o digrafo _não_ é um DAG, ORDER() RETORNA -1.
 */
vertex
order(Topological ts, Bool init)
{
    if (!isDag(ts))
        return (-1);
    if (init) 
        ts->orderCycleCounter = 0;
    if (ts->orderCycleCounter == ts->V)
        return (-1);
    return (ts->order[ts->orderCycleCounter++]);
}

/*-----------------------------------------------------------*/
/* 
 *  CYCLE(TS, INIT)
 * 
 *  RECEBE uma representação topológica TS de um digrafo e um Bool INIT.
 *
 *  Se INIT é TRUE,  CYCLE() RETORNA um vértice em um ciclo do digrafo.
 *  Se INIT é FALSE, CYCLE() RETORNA o vértice  no ciclo que é sucessor do 
 *                   último vértice retornado; se todos os vértices no ciclo já 
 *                   foram retornados, a função retorna -1.
 *
 *  Se o digrafo é um DAG, CYCLE() RETORNA -1.
 *
 */
vertex
cycle(Topological ts, Bool init)
{
    if (isDag(ts))
        return (-1);
    if (init) 
        ts->orderCycleCounter = 0;
    if (ts->orderCycleCounter == ts->cycleLen)
        return (-1);
    return (ts->cycle[ts->orderCycleCounter++]);    
}


/*------------------------------------------------------------*/
/* 
 * Implementaçao de funções administrativas: têm o modificador 
 * static.
 */
static
void dfs(Topological ts, Digraph G, vertex v)
{
    int w;
    ts->marked[v] = TRUE;
    ts->onStack[v] = TRUE; 
    ts->pre[v] = ts->preCounter;
    ts->preOrder[ts->preCounter++] = v;
    for (w = adj(G, v, TRUE); w != -1; w = adj(G, v, FALSE)) {
        if (!ts->marked[w]) {
            ts->edgeTo[w] = v;
            dfs(ts, G, w);
        } else if (ts->onStack[w] && ts->cycle == NULL) {
            vertex x, i = 0, j;
            for (x = v; x != w; x = ts->edgeTo[x], i++);
            ts->cycleLen = 1 + i;
            ts->cycle = emalloc (ts->cycleLen * sizeof (vertex));
            ts->cycle[0] = w; 
            for (x = v, j = 1; x != w; x = ts->edgeTo[x], j++)
                ts->cycle[ts->cycleLen - j] = x;
        }
    }
    ts->postOrder[ts->postCounter] = v;
    ts->post[v] = ts->postCounter++;
    ts->onStack[v] = FALSE;
}

