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
 * ADT Digraph implementada atrevés de vetor de listas de adjacência.
 * As listas de adjacência são bag de ints que são mais restritos 
 * que as bags genéricas do EP12. Veja a api bag.h e simplifique 
 * o EP12 de acordo. 
 *  
 * Busque inspiração em: 
 *
 *    https://algs4.cs.princeton.edu/42digraph/ (Graph representation)
 *    https://algs4.cs.princeton.edu/42digraph/Digraph.java.html
 * 
 * DIGRAPH
 *
 * Digraph representa um grafo orientado de vértices inteiros de 0 a V-1. 
 * 
 * As principais operações são: add() que insere um arco no digrafo, e
 * adj() que itera sobre todos os vértices adjacentes a um dado vértice.
 * 
 * Arcos paralelos e laços são permitidos.
 * 
 * Esta implementação usa uma representação de _vetor de listas de adjacência_,
 * que  é uma vetor de objetos Bag indexado por vértices. 

 * ATENÇÃO: Por simplicidade esses Bag podem ser int's e não de Integer's.
 *
 * Todas as operações consomen no pior caso tempo constante, exceto
 * iterar sobre os vértices adjacentes a um determinado vértice, cujo 
 * consumo de tempo é proporcional ao número de tais vértices.
 * 
 * Para documentação adicional, ver 
 * https://algs4.cs.princeton.edu/42digraph, Seção 4.2 de
 * Algorithms, 4th Edition por Robert Sedgewick e Kevin Wayne.
 *
 */

/* interface para o uso da funcao deste módulo */
#include "digraph.h"


#include "bag.h"     /* add() e itens() */
#include <stdio.h>   /* fopen(), fclose(), fscanf(), ... */
#include <stdlib.h>  /* free() */
#include <string.h>  /* memcpy() */
#include "util.h"    /* emalloc(), ecalloc() */

#undef DEBUG
#ifdef DEBUG
#include <stdio.h>   /* printf(): para debuging */
#endif

/*----------------------------------------------------------*/
/* 
 * Estrutura básica de um Digraph
 * 
 * Implementação com vetor de listas de adjacência.
 */
struct digraph 
{
    int V;
    int E;
    Bag* adj;
    int* indegree;
};

/*------------------------------------------------------------*/
/* 
 * Protótipos de funções administrativas: tem modificador 'static'
 * 
 */
void  
addEdge(Digraph G, vertex v, vertex w);

int 
adj(Digraph G, vertex v, Bool init);

static Bool
isValidVertex(Digraph G, vertex v);

static char 
*intToString(int num);

static char
*append(char *dest, const char *src);

/*-----------------------------------------------------------*/
/*
 *  newDigraph(V)
 *
 *  RECEBE um inteiro V.
 *  RETORNA um digrafo com V vértices e 0 arcos.
 * 
 */
Digraph
newDigraph(int V)
{
    if (V < 0) {
        printf ("O número de vértices deve ser não negativo.");
        return (NULL);
    }
    int v;
    Digraph G = emalloc (sizeof (struct digraph));
    G->V = V;
    G->E = 0;
    G->indegree = emalloc (V * sizeof (int));
    G->adj = emalloc (V * sizeof (Bag));
    for (v = 0; v < V; v++)
        G->adj[v] = newBag();
    return (G);
}

/*-----------------------------------------------------------*/
/*
 *  cloneDigraph(G)
 *
 *  RECEBE um digrafo G.
 *  RETORNA um clone de G.
 * 
 */
Digraph
cloneDigraph(Digraph G)
{
    int v;
    Digraph Clone = emalloc (sizeof (struct digraph));
    Clone->V = G->V;
    Clone->E = G->E;
    Clone->indegree = emalloc (G->V * sizeof (int));
    Clone->adj = emalloc(G->V * sizeof(Bag));
    for (v = 0; v < G->V; v++) {
        Clone->indegree[v] = G->indegree[v];
        Clone->adj[v] = newBag();
        vertex w;
        for (w = adj(G, v, TRUE); w != -1; w = adj(G, v, FALSE))
            add(Clone->adj[v], w);   
    }
    return (Clone);
}

/*-----------------------------------------------------------*/
/*
 *  reverseDigraph(G)
 *
 *  RECEBE um digrafo G.
 *  RETORNA o digrafo R que é o reverso de G: 
 *
 *      v-w é arco de G <=> w-v é arco de R.
 * 
 */
Digraph
reverseDigraph(Digraph G)
{
    Digraph reverse = newDigraph(G->V);
    int v, w;
    for (v = 0; v < G->V; v++) {
        for (w = adj(G, v, TRUE); w != -1; w = adj(G, v, FALSE))
            addEdge(reverse, w, v);   
    }
    return (reverse);
}

/*-----------------------------------------------------------*/
/*
 *  readDigraph(NOMEARQ)
 *
 *  RECEBE uma stringa NOMEARQ.
 *  RETORNA o digrafo cuja representação está no arquivo de nome NOMEARQ.
 *  O arquivo contém o número de vértices V, seguido pelo número de arestas E,
 *  seguidos de E pares de vértices, com cada entrada separada por espaços.
 *
 *  Veja os arquivos  tinyDG.txt, mediumDG.txt e largeDG.txt na página do 
 *  EP e que foram copiados do algs4, 
 * 
 */
Digraph
readDigraph(String nomeArq)
{
    FILE *digraphFile;
    Digraph G;
    int V, E, v, w;
    digraphFile = fopen (nomeArq, "r");
    fscanf (digraphFile, "%d", &V);
    fscanf (digraphFile, "%d", &E);
    if (E < 0) {
        printf ("number of edges in a Digraph must be nonnegative.\n");
        return (NULL);
    }
    G = newDigraph(V);
    for (; E > 0; E--) {
        fscanf (digraphFile, "%d", &v); 
        fscanf (digraphFile, "%d", &w);
        addEdge(G, v, w);
    }
    fclose (digraphFile);
    return (G);
}


/*-----------------------------------------------------------*/
/*
 *  freeDigraph(G)
 *
 *  RECEBE um digrafo G e retorna ao sistema toda a memória 
 *  usada por G.
 *
 */
void  
freeDigraph(Digraph G)
{
    int v;
    for (v = 0; v < G->V; v++)
        freeBag(G->adj[v]);
    free (G->adj);
    free (G->indegree);
    free (G);
}    

/*------------------------------------------------------------*/
/*
 * OPERAÇÕES USUAIS: 
 *
 *     - vDigraph(), eDigraph(): número de vértices e arcos
 *     - addEdge(): insere um arco
 *     - adj(): itera sobre os vizinhos de um dado vértice
 *     - outDegree(), inDegree(): grau de saída e de entrada
 *     - toString(): usada para exibir o digrafo 
 */

/*-----------------------------------------------------------*/
/* 
 *  VDIGRAPH(G)
 *
 *  RECEBE um digrafo G e RETORNA seu número de vertices.
 *
 */
int
vDigraph(Digraph G)
{
    return (G->V);
    
}

/*-----------------------------------------------------------*/
/* 
 *  EDIGRAPH(G)
 *
 *  RECEBE um digrafo G e RETORNA seu número de arcos (edges).
 *
 */
int
eDigraph(Digraph G)
{
    return (G->E);
}

/*-----------------------------------------------------------*/
/*
 *  addEdge(G, V, W)
 * 
 *  RECEBE um digrafo G e vértice V e W e INSERE o arco V-W  
 *  em G.
 *
 */
void  
addEdge(Digraph G, vertex v, vertex w)
{
    if (!isValidVertex(G, v) || !isValidVertex(G, w))
        return;
    add(G->adj[v], w);
    G->indegree[w]++;
    G->E++;
}    


/*-----------------------------------------------------------*/
/* 
 *  ADJ(G, V, INIT)
 * 
 *  RECEBE um digrafo G, um vértice v de G e um Bool INIT.
 *
 *  Se INIT é TRUE,  ADJ() RETORNA o primeiro vértice na lista de adjacência de V.
 *  Se INIT é FALSE, ADJ() RETORNA o sucessor na lista de adjacência de V do 
 *                   último vértice retornado.
 *  Se a lista de adjacência de V é vazia ou não há sucessor do último vértice 
 *  retornada, ADJ() RETORNA -1.
 *
 *  Se entre duas chamadas de ADJ() a lista de adjacência de V é alterada, 
 *  o comportamento é  indefinido. 
 *  
 */
int 
adj(Digraph G, vertex v, Bool init)
{
    return (itens(G->adj[v], init));
}

/*-----------------------------------------------------------*/
/*
 *  outDegree(G, V)
 * 
 *  RECEBE um digrafo G e vértice V.
 *  RETORNA o número de arcos saindo de V.
 *
 */
int
outDegree(Digraph G, vertex v)
{
    if (!isValidVertex(G, v))
        return (-1);
    return (size(G->adj[v]));
}

/*-----------------------------------------------------------*/
/*
 *  inDegree(G, V)
 * 
 *  RECEBE um digrafo G e vértice V.
 *  RETORNA o número de arcos entrando em V.
 *
 */
int
inDegree(Digraph G, vertex v)
{
    if (!isValidVertex(G, v))
        return (-1);
    return (G->indegree[v]);
}


/*-----------------------------------------------------------*/
/*
 *  toString(G)
 * 
 *  RECEBE um digrafo G.
 *  RETORNA uma string que representa G. Essa string será usada
 *  para exibir o digrafo: printf("%s", toString(G)); 
 *    
 *  Sigestão: para fazer esta função inspire-se no método 
 *  toString() da classe Digraph do algs4.
 */
String
toString(Digraph G)
{
    char *s, *v, *w;
    int i, j;
    v = intToString(G->V); w = intToString(G->E);
    s = emalloc ((17 + strlen(v) + strlen(w)) * sizeof (char));
    sprintf(s, "%svertices, %sedges\n", v, w);
    for (i = 0; i < G->V; i++) {
        free (v);
        v = intToString(i); v[strlen(v) - 1] = ':';
        s = append(s, v);
        for (j = adj(G, i, TRUE); j != -1; j = adj(G, i, FALSE)) {
            free (w);
            w = intToString(j);
            s = append(s, w);
        }
        s = append(s, "\n");
    }
    free (v); free (w);
    return (s);
}

/*------------------------------------------------------------*/
/* 
 * Implementaçao de funções administrativas: têm o modificador 
 * static.
 */
static Bool
isValidVertex(Digraph G, vertex v)
{
    if (v < 0 || v >= G->V) {
        printf ("O vertice deve estar entre 0 e %d", G->V - 1);
        return (FALSE);
    }
    return (TRUE);
}

static char
*intToString(int num)
{
    int digits = 0, aux = num, i;
    char *s;
    if (aux == 0) 
        digits = 1; 
    while (aux > 0) {
        aux = aux / 10;
        digits++;
    }
    s = emalloc ((digits + 2) * sizeof (char));
    s[digits + 1] = '\0'; s[digits] = ' ';
    for (i = digits - 1; i >= 0; i--) {
        s[i] = (num % 10) + '0';
        num = num / 10;
    }
    return (s);
}

static char
*append(char *dest, const char *src)
{
    char *temp = emalloc ((strlen(dest) + strlen(src) + 1) * sizeof (char));
    strcpy(temp, dest); strcat(temp, src); free (dest);
    return (temp);
}