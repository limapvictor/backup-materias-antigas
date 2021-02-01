/****************************************************************
    Nome: Victor Pereira Lima
    NUSP: 10737028

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
    A maioria dos métodos foram basicamente uma adaptação dos métodos vistos aqui:
    https://algs4.cs.princeton.edu/33balanced/RedBlackBST.java.html

    Se for o caso, descreva a seguir 'bugs' e limitações do seu programa:

****************************************************************/
/*
 * MAC0323 Estruturas de Dados e Algoritmo II
 * 
 * Tabela de simbolos implementada atraves de uma BST rubro-negra
 *
 *     https://algs4.cs.princeton.edu/33balanced/RedBlackBST.java.html
 * 
 * As chaves e valores desta implementação são mais ou menos
 * genéricos
 */

/* interface para o uso da funcao deste módulo */
#include "redblackst.h"  

#include <stdlib.h>  /* free() */
#include <string.h>  /* memcpy() */
#include "util.h"    /* emalloc(), ecalloc() */

#undef DEBUG
#ifdef DEBUG
#include <stdio.h>   /* printf(): para debug */
#endif

/*
 * CONSTANTES 
 */
#define RED   TRUE
#define BLACK FALSE 

/*----------------------------------------------------------*/
/* 
 * Estrutura Básica da Tabela de Símbolos: 
 * 
 * implementação com árvore rubro-negra
 */
typedef struct node *Node;
struct redBlackST {
    Node root;
    int (*compareTo)(const void* key1, const void* key2);
    int lastKeyReturned;
};

/*----------------------------------------------------------*/
/* 
 * Estrutura de um nó da árvore
 *
 */
struct node {
    void* key;
    void* val;
    size_t sizeKey, sizeVal;
    Node left, right;
    Bool color;
    int size;
};

/*------------------------------------------------------------*/
/* 
 *  Protótipos de funções administrativas.
 * 
 *  Entre essa funções estão isRed(), rotateLeft(), rotateRight(),
 *  flipColors(), moveRedLeft(), moveRedRight() e balance().
 * 
 *  Não deixe de implmentar as funções chamadas pela função 
 *  check(): isBST(), isSizeConsistent(), isRankConsistent(),
 *  is23(), isBalanced().
 *
 */
/*---------------------------------------------------------------*/
static Bool
isBST(RedBlackST st);
static Bool
isBSTRecursive(RedBlackST st, Node x, const void* keyMin, const void* keyMax);

/*---------------------------------------------------------------*/
static Bool
isSizeConsistent(RedBlackST st);
static Bool
isSizeConsistentRecursive(Node x);

/*---------------------------------------------------------------*/
static Bool
isRankConsistent(RedBlackST st);

/*---------------------------------------------------------------*/
static Bool
is23(RedBlackST st);
static Bool
is23Recursive(Node root, Node x);

/*---------------------------------------------------------------*/
static Bool
isBalanced(RedBlackST st);
static Bool
isBalancedRecursive(Node x, int black);

/*---------------------------------------------------------------*/
void
freeNodes(Node x);

/*---------------------------------------------------------------*/
Node 
putPrivate(RedBlackST st, Node x, const void *key, size_t sizeKey, const void *val, size_t sizeVal);

/*---------------------------------------------------------------*/
Node 
getPrivate(RedBlackST st, Node x, const void *key);

/*---------------------------------------------------------------*/
Node
deletePrivate(RedBlackST st, Node x, const void *key);

/*---------------------------------------------------------------*/
Node
deleteMinPrivate(Node x);

/*---------------------------------------------------------------*/
Node
deleteMaxPrivate(Node x);

/*---------------------------------------------------------------*/
int
sizePrivate(Node x);

/*---------------------------------------------------------------*/
int
rankPrivate(RedBlackST st, Node x, const void *key);

/*---------------------------------------------------------------*/
int
heightPrivate(Node x);

/*---------------------------------------------------------------*/
Node 
selectPrivate(Node x, int k);

/*---------------------------------------------------------------*/
Bool
isRed(Node x);

/*---------------------------------------------------------------*/
Node 
rotateLeft(Node x);

/*---------------------------------------------------------------*/
Node 
rotateRight(Node x);

/*---------------------------------------------------------------*/
void 
flipColors(Node x);

/*---------------------------------------------------------------*/
Node 
moveRedLeft(Node x);

/*---------------------------------------------------------------*/
Node 
moveRedRight(Node x);

/*---------------------------------------------------------------*/
Node 
balance(Node x);

/*-----------------------------------------------------------*/
/*
 *  initST(COMPAR)
 *
 *  RECEBE uma função COMPAR() para comparar chaves.
 *  RETORNA (referência/ponteiro para) uma tabela de símbolos vazia.
 *
 *  É esperado que COMPAR() tenha o seguinte comportamento:
 *
 *      COMPAR(key1, key2) retorna um inteiro < 0 se key1 <  key2
 *      COMPAR(key1, key2) retorna 0              se key1 == key2
 *      COMPAR(key1, key2) retorna um inteiro > 0 se key1 >  key2
 * 
 *  TODAS OS OPERAÇÕES da ST criada utilizam a COMPAR() para comparar
 *  chaves.
 * 
 */
RedBlackST
initST(int (*compar)(const void *key1, const void *key2))
{
    RedBlackST st = emalloc (sizeof (struct redBlackST));
    st->root = NULL;
    st->compareTo = compar;
    st->lastKeyReturned = 0;
    return (st); 
}

/*-----------------------------------------------------------*/
/*
 *  freeST(ST)
 *
 *  RECEBE uma RedBlackST  ST e devolve ao sistema toda a memoria 
 *  utilizada por ST.
 *
 */
void  
freeST(RedBlackST st)
{
    freeNodes(st->root);
    free (st);
}

void 
freeNodes(Node x)
{
    if (x != NULL) {
        freeNodes(x->left);
        freeNodes(x->right);
        free (x->key); free (x->val);
        free (x);
    }
}

/*------------------------------------------------------------*/
/*
 * OPERAÇÕES USUAIS: put(), get(), contains(), delete(),
 * size() e isEmpty().
 */

/*-----------------------------------------------------------*/
/*
 *  put(ST, KEY, NKEY, VAL, NVAL)
 * 
 *  RECEBE a tabela de símbolos ST e um par KEY-VAL e procura a KEY na ST.
 *
 *     - se VAL é NULL, a entrada da chave KEY é removida da ST  
 *  
 *     - se KEY nao e' encontrada: o par KEY-VAL é inserido na ST
 *
 *     - se KEY e' encontra: o valor correspondente é atualizado
 *
 *  NKEY é o número de bytes de KEY e NVAL é o número de bytes de NVAL.
 *
 *  Para criar uma copia/clone de KEY é usado o seu número de bytes NKEY.
 *  Para criar uma copia/clode de VAL é usado o seu número de bytes NVAL.
 *
 */

void  
put(RedBlackST st, const void *key, size_t sizeKey, const void *val, size_t sizeVal)
{
    if (key == NULL) 
        return;
    if (val == NULL) {
        delete(st, key);
        return;
    }
    st->root = putPrivate(st, st->root, key, sizeKey, val, sizeVal);
    st->root->color = BLACK;
}    

Node
putPrivate(RedBlackST st, Node x, const void *key, size_t sizeKey, const void *val, size_t sizeVal)
{
    if (x == NULL) {
        x = emalloc (sizeof (struct node));
        x->key = emalloc (sizeKey); memcpy (x->key, key, sizeKey);
        x->val = emalloc (sizeVal); memcpy (x->val, val, sizeVal);
        x->sizeKey = sizeKey; x->sizeVal = sizeVal;
        x->left = NULL; x->right = NULL;
        x->color = RED;
        x->size = 1;
        return (x);
    }
    int cmp = st->compareTo(key, x->key);
    if (cmp < 0)
        x->left = putPrivate(st, x->left, key, sizeKey, val, sizeVal);
    else if (cmp > 0)
        x->right = putPrivate(st, x->right, key, sizeKey, val, sizeVal);
    else {
        free (x->val);
        x->val = emalloc (sizeVal); memcpy (x->val, val, sizeVal);
    }
    if (isRed(x->right) && !isRed(x->left))
        x = rotateLeft(x);
    if (isRed(x->left)  &&  isRed(x->left->left)) 
        x = rotateRight(x);
    if (isRed(x->left)  &&  isRed(x->right))     
        flipColors(x);
    x->size = sizePrivate(x->left) + sizePrivate(x->right) + 1;
    return (x);
}

/*-----------------------------------------------------------*/
/*
 *  get(ST, KEY)
 *
 *  RECEBE uma tabela de símbolos ST e uma chave KEY.
 *
 *     - se KEY está em ST, RETORNA NULL;
 *
 *     - se KEY não está em ST, RETORNA uma cópia/clone do valor
 *       associado a KEY.
 * 
 */
void *
get(RedBlackST st, const void *key)
{
    if (key == NULL)
        return;
    Node x = getPrivate(st, st->root, key);
    if (x != NULL) {
        void *cloneVal = emalloc (x->sizeVal);
        memcpy (cloneVal, x->val, x->sizeVal);
        return (cloneVal);
    }
    return (NULL);
}

Node
getPrivate(RedBlackST st, Node x, const void *key)
{
    if (x != NULL) {
        int cmp = st->compareTo(key, x->key);
        if (cmp < 0)
            return (getPrivate(st, x->left, key));
        else if (cmp > 0)
            return (getPrivate(st, x->right, key));
        else
            return (x);
    }
    return (NULL);   
}


/*-----------------------------------------------------------*/
/* 
 *  CONTAINS(ST, KEY)
 *
 *  RECEBE uma tabela de símbolos ST e uma chave KEY.
 * 
 *  RETORNA TRUE se KEY está na ST e FALSE em caso contrário.
 *
 */
Bool
contains(RedBlackST st, const void *key)
{
    void* getResult = get(st, key);
    Bool containsResult = FALSE;
    if (getResult != NULL)
        containsResult = TRUE;
    free (getResult);
    return (containsResult);
}

/*-----------------------------------------------------------*/
/* 
 *  DELETE(ST, KEY)
 *
 *  RECEBE uma tabela de símbolos ST e uma chave KEY.
 * 
 *  Se KEY está em ST, remove a entrada correspondente a KEY.
 *  Se KEY não está em ST, faz nada.
 *
 */
void
delete(RedBlackST st, const void *key)
{
    if (key == NULL || !contains(st, key))
        return;
     if (!isRed(st->root->left) && !isRed(st->root->right))
            st->root->color = RED;
    st->root = deletePrivate(st, st->root, key);
    if (!isEmpty(st)) 
        st->root->color = BLACK;
}

Node
deletePrivate(RedBlackST st, Node x, const void *key)
{
    if (st->compareTo(key, x->key) < 0) {
        if (!isRed(x->left) && !isRed(x->left->left))
                x = moveRedLeft(x);
        x->left = deletePrivate(st, x->left, key);
    } else {
        if (isRed(x->left))
            x = rotateRight(x);
        if (st->compareTo(key, x->key) == 0 && (x->right == NULL)) {
            free (x->key); free (x->val);
            free (x);
            return (NULL);
        }
        if (!isRed(x->right) && !isRed(x->right->left))
            x = moveRedRight(x);
        if (st->compareTo(key, x->key) == 0) {
            Node h = x->right;
            while (h-> left != NULL)
                h = h->left;
            x->key = h->key;
            x->val = h->val;
            x->right = deleteMinPrivate(x->right);
        } else
            x->right = deletePrivate(st, x->right, key);
    }
    return (balance(x));
}

/*-----------------------------------------------------------*/
/* 
 *  SIZE(ST)
 *
 *  RECEBE uma tabela de símbolos ST.
 * 
 *  RETORNA o número de itens (= pares chave-valor) na ST.
 *
 */
int
size(RedBlackST st)
{
    return (sizePrivate(st->root));
}

int
sizePrivate(Node x)
{
    if (x == NULL)
        return (0);
    return (x->size);
}

/*-----------------------------------------------------------*/
/* 
 *  ISEMPTY(ST, KEY)
 *
 *  RECEBE uma tabela de símbolos ST.
 * 
 *  RETORNA TRUE se ST está vazia e FALSE em caso contrário.
 *
 */
Bool
isEmpty(RedBlackST st)
{
    return (st->root == NULL);
}

/*------------------------------------------------------------*/
/*
 * OPERAÇÕES PARA TABELAS DE SÍMBOLOS ORDENADAS: 
 * min(), max(), rank(), select(), deleteMin() e deleteMax().
 */

/*-----------------------------------------------------------*/
/*
 *  MIN(ST)
 * 
 *  RECEBE uma tabela de símbolos ST e RETORNA uma cópia/clone
 *  da menor chave na tabela.
 *
 *  Se ST está vazia RETORNA NULL.
 *
 */
void *
min(RedBlackST st)
{
    if (isEmpty(st))
        return (NULL);
    Node min = st->root;
    while (min->left != NULL)
        min = min->left;
    void *cloneKey = emalloc (min->sizeKey);
    memcpy (cloneKey, min->key, min->sizeKey);
    return (cloneKey);
}


/*-----------------------------------------------------------*/
/*
 *  MAX(ST)
 * 
 *  RECEBE uma tabela de símbolos ST e RETORNA uma cópia/clone
 *  da maior chave na tabela.
 *
 *  Se ST está vazia RETORNA NULL.
 *
 */
void *
max(RedBlackST st)
{
    if (isEmpty(st))
        return (NULL);
    Node max = st->root;
    while (max->right != NULL)
        max = max->right;
    void *cloneKey = emalloc (max->sizeKey);
    memcpy (cloneKey, max->key, max->sizeKey);
    return (cloneKey);
}


/*-----------------------------------------------------------*/
/*
 *  RANK(ST, KEY)
 * 
 *  RECEBE uma tabela de símbolos ST e uma chave KEY.
 *  RETORNA o número de chaves em ST menores que KEY.
 *
 *  Se ST está vazia RETORNA NULL.
 *
 */
int
rank(RedBlackST st, const void *key)
{
    if (isEmpty(st) || key == NULL)
        return (NULL);
    return (rankPrivate(st, st->root, key));
} 

int
rankPrivate(RedBlackST st, Node x, const void *key)
{
    if (x == NULL)
        return (0);
    int cmp = st->compareTo(key, x->key);
    if (cmp < 0)
        return (rankPrivate(st, x->left, key));
    else if (cmp > 0)
        return (1 + sizePrivate(x->left) + rankPrivate(st, x->right, key));
    else
        return (sizePrivate(x->left));
}

/*-----------------------------------------------------------*/
/*
 *  SELECT(ST, K)
 * 
 *  RECEBE uma tabela de símbolos ST e um inteiro K >= 0.
 *  RETORNA a (K+1)-ésima menor chave da tabela ST.
 *
 *  Se ST não tem K+1 elementos RETORNA NULL.
 *
 */
void *
select(RedBlackST st, int k)
{
    if (k < 0 || k >= size(st))
        return (NULL);
    Node x = selectPrivate(st->root, k);
    void *cloneKey = emalloc (x->sizeKey);
    memcpy (cloneKey, x->key, x->sizeKey);
    return (cloneKey);
}

Node 
selectPrivate(Node x, int k)
{
    int t = sizePrivate(x->left); 
    if (t > k) 
        return (selectPrivate(x->left, k)); 
    else if (t < k)
        return (selectPrivate(x->right, k - t - 1)); 
    else            
        return (x); 
}

/*-----------------------------------------------------------*/
/*
 *  deleteMIN(ST)
 * 
 *  RECEBE uma tabela de símbolos ST e remove a entrada correspondente
 *  à menor chave.
 *
 *  Se ST está vazia, faz nada.
 *
 */
void
deleteMin(RedBlackST st)
{
    if (isEmpty(st))
        return;
     if (!isRed(st->root->left) && !isRed(st->root->right))
            st->root->color = RED;
    st->root = deleteMinPrivate(st->root);
    if (!isEmpty(st))
        st->root->color = BLACK;
}

Node
deleteMinPrivate(Node x)
{
    if (x->left == NULL) { 
        free (x->key); free (x->val);
        free (x);
        return (NULL);
    }
    if (!isRed(x->left) && !isRed(x->left->left))
        x = moveRedLeft(x);
    x->left = deleteMinPrivate(x->left);
    return (balance(x));
}

/*-----------------------------------------------------------*/
/*
 *  deleteMAX(ST)
 * 
 *  RECEBE uma tabela de símbolos ST e remove a entrada correspondente
 *  à maior chave.
 *
 *  Se ST está vazia, faz nada.
 *
 */
void
deleteMax(RedBlackST st)
{
    if (isEmpty(st))
        return;
     if (!isRed(st->root->left) && !isRed(st->root->right))
            st->root->color = RED;
    st->root = deleteMaxPrivate(st->root);
    if (!isEmpty(st))
        st->root->color = BLACK;
}

Node
deleteMaxPrivate(Node x)
{
    if (isRed(x->left))
        x = rotateRight(x);
    if (x->right == NULL) {
        free (x->key); free (x->val);
        free (x);
        return (NULL);
    }
    if (!isRed(x->right) && !isRed(x->right->left))
        x = moveRedRight(x);
    x->right = deleteMaxPrivate(x->right);
    return (balance(x));
}


/*-----------------------------------------------------------*/
/* 
 *  KEYS(ST, INIT)
 * 
 *  RECEBE uma tabela de símbolos ST e um Bool INIT.
 *
 *  Se INIT é TRUE, KEYS() RETORNA uma cópia/clone da menor chave na ST.
 *  Se INIT é FALSE, KEYS() RETORNA a chave sucessora da última chave retornada.
 *  Se ST está vazia ou não há sucessora da última chave retornada, KEYS() retorna NULL.
 *
 *  Se entre duas chamadas de KEYS() a ST é alterada, o comportamento é 
 *  indefinido. 
 *  
 */
void * 
keys(RedBlackST st, Bool init)
{
    if (isEmpty(st) || st->lastKeyReturned == size(st) - 1) {
        st->lastKeyReturned = 0;
        return (NULL);
    }
    if (init)
        return (min(st));
    else 
        return (select(st, ++st->lastKeyReturned));
}



/*------------------------------------------------------------*/
/* 
 * Funções administrativas
 */

/***************************************************************************
 *  Utility functions.
 ***************************************************************************/

/*
 * HEIGHT(ST)
 * 
 * RECEBE uma RedBlackST e RETORNA a sua altura. 
 * Uma BST com apenas um nó tem altura zero.
 * 
 */
int
height(RedBlackST st)
{
        return (heightPrivate(st->root));
}

int
heightPrivate(Node x)
{
    if (x == NULL)
        return (-1);
    int heightLeft = heightPrivate(x->left), heightRight = heightPrivate(x->right);
    if (heightLeft > heightRight)
        return (1 + heightLeft);
    return (1 + heightRight);
}

/***************************************************************************
 *  Check integrity of red-black tree data structure.
 ***************************************************************************/
Bool
isRed(Node x)
{
    if (x == NULL) 
        return (FALSE);
    return (x->color == RED);
}

Node
rotateRight(Node x)
{
    Node aux = x->left;
    x->left = aux->right;
    aux->right = x;
    aux->color = aux->right->color;
    aux->right->color = RED;
    aux->size = x->size;
    x->size = sizePrivate(x->left) + sizePrivate(x->right) + 1;
    return (aux);
}

Node
rotateLeft(Node x)
{
    Node aux = x->right;
    x->right = aux->left;
    aux->left = x;
    aux->color = aux->left->color;
    aux->left->color = RED;
    aux->size = x->size;
    x->size = sizePrivate(x->left) + sizePrivate(x->right) + 1;
    return (aux);
}


void
flipColors(Node x)
{
    x->color = !x->color;
    x->left->color = !x->left->color;
    x->right->color = !x->right->color;
}

Node 
moveRedLeft(Node x)
{
    flipColors(x);
    if (isRed(x->right->left)) { 
        x->right = rotateRight(x->right);
        x = rotateLeft(x);
        flipColors(x);
    }
    return (x);
}

Node 
moveRedRight(Node x)
{
    flipColors(x);
    if (isRed(x->left->left)) { 
        x = rotateRight(x);
        flipColors(x);
    }
    return (x);
}

Node
balance(Node x)
{
     if (isRed(x->right))
        x = rotateLeft(x);
    if (isRed(x->left) && isRed(x->left->left)) 
        x = rotateRight(x);
    if (isRed(x->left) && isRed(x->right))     
        flipColors(x);
    x->size = sizePrivate(x->left) + sizePrivate(x->right) + 1;
    return (x);
}

/*
 * CHECK(ST)
 *
 * RECEBE uma RedBlackST ST e RETORNA TRUE se não encontrar algum
 * problema de ordem ou estrutural. Em caso contrário RETORNA 
 * FALSE.
 * 
 */
Bool
check(RedBlackST st)
{
    if (!isBST(st))            ERROR("check(): not in symmetric order");
    if (!isSizeConsistent(st)) ERROR("check(): subtree counts not consistent");
    if (!isRankConsistent(st)) ERROR("check(): ranks not consistent");
    if (!is23(st))             ERROR("check(): not a 2-3 tree");
    if (!isBalanced(st))       ERROR("check(): not balanced");
    return isBST(st) && isSizeConsistent(st) && isRankConsistent(st) && is23(st) && isBalanced(st);
}


/* 
 * ISBST(ST)
 * 
 * RECEBE uma RedBlackST ST.
 * RETORNA TRUE se a árvore é uma BST.
 * 
 */
static Bool
isBST(RedBlackST st)
{
    return (isBSTRecursive(st, st->root, NULL, NULL));
}

static Bool
isBSTRecursive(RedBlackST st, Node x, const void* keyMin, const void* keyMax)
{
    if (x == NULL)
        return (TRUE);
    if (keyMin != NULL && st->compareTo(x->key, keyMin) <= 0)
        return (FALSE);
    if (keyMax != NULL && st->compareTo(x->key, keyMax) >= 0)
        return (FALSE);
    return (isBSTRecursive(st, x->left, keyMin, x->key) && isBSTRecursive(st, x->right, x->key, keyMax));
}
/* 
 *  ISSIZECONSISTENT(ST) 
 *
 *  RECEBE uma RedBlackST ST e RETORNA TRUE se para cada nó h
 *  vale que size(h) = 1 + size(h->left) + size(h->right) e 
 *  FALSE em caso contrário.
 */
static Bool
isSizeConsistent(RedBlackST st)
{
    return (isSizeConsistentRecursive(st->root));
}

static Bool
isSizeConsistentRecursive(Node x)
{
    if (x == NULL) 
        return (TRUE);
    if (x->size != sizePrivate(x->left) + sizePrivate(x->right) + 1)
        return (FALSE);
    return (isSizeConsistentRecursive(x->left) && isSizeConsistentRecursive(x->right));
}

/* 
 *  ISRANKCONSISTENT(ST)
 *
 *  RECEBE uma RedBlackST ST e RETORNA TRUE se seus rank() e
 *  select() são consistentes.
 */  
/* check that ranks are consistent */
static Bool
isRankConsistent(RedBlackST st)
{
    int i;
    void *keySelected, *key;
    Bool isConsistent = TRUE;
    for (i = 0; i < size(st) && isConsistent; i++) {
        keySelected = select(st, i);
        if (i != rank(st, keySelected))
            isConsistent = FALSE;
        free (keySelected);
    }
    for (key = keys(st, TRUE); key && isConsistent; key = keys(st,FALSE)) {
        keySelected = select(st, rank(st, key));
        if (st->compareTo(key, keySelected) != 0)
            isConsistent = FALSE;
        free (keySelected); free (key);
    }
    return (isConsistent);
}

/* 
 *  IS23(ST)
 *
 *  RECEBE uma RedBlackST ST e RETORNA FALSE se há algum link RED
 *  para a direta ou se ha dois links para esquerda seguidos RED 
 *  Em caso contrário RETORNA TRUE (= a ST representa uma árvore 2-3). 
 */
static Bool
is23(RedBlackST st)
{
    return (is23Recursive(st->root, st->root));
}

static Bool
is23Recursive(Node root, Node x)
{
    if (x == NULL)
        return (TRUE);
    if (isRed(x->right))
        return (FALSE);
    if (x != root && isRed(x) && isRed(x->left))
        return (FALSE);
    return (is23Recursive(root, x->left) && is23Recursive(root, x->right));
}

/* 
 *  ISBALANCED(ST) 
 * 
 *  RECEBE uma RedBlackST ST e RETORNA TRUE se st satisfaz
 *  balanceamento negro perfeiro.
 */ 
static Bool
isBalanced(RedBlackST st)
{
    int black = 0;
    Node x = st->root;
    while (x != NULL) {
        if (!isRed(x))
            black++;
        x = x->left;
    }
    return isBalancedRecursive(st->root, black);
}

static Bool
isBalancedRecursive(Node x, int black)
{
        if (x == NULL)
            return (black == 0);
        if (!isRed(x)) 
            black--;
        return (isBalancedRecursive(x->left, black) && isBalancedRecursive(x->right, black));
} 

