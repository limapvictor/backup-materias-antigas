/*
 * MAC0323 Estruturas de Dados e Algoritmo II
 * 
 * Tabela de simbolos implementada atraves de vetores ordenados 
 * redeminsionaveis 
 *
 *     https://algs4.cs.princeton.edu/31elementary/BinarySearchST.java.html
 * 
 * As chaves e valores desta implementação são mais ou menos
 * genéricos
 */

/* interface para o uso da funcao deste módulo */
#include "binarysearchst.h"  

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

/*------------------------------------------------------------*/
/* 
 * Funções administrativas
 */
/*----------------------------------------------------------*/
/* 
 * Estrutura Básica da Tabela de Símbolos: 
 * 
 * implementação com vetores ordenados
 */
struct sizeKeyVal{
    size_t sizeKey, sizeVal;
};
typedef struct sizeKeyVal sizeKeyVal;

struct binarySearchST {
    void** keys;
    void** vals;
    sizeKeyVal* sizes;
    int capacity, N, lastKeyReturned;
    int (*compareTo)(const void *key1, const void *key2);
};

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
BinarySearchST
initST(int (*compar)(const void *key1, const void *key2))
{
    BinarySearchST st = emalloc (sizeof (struct binarySearchST));
    st->capacity = 2;
    st->keys = emalloc (st->capacity * sizeof (void *));
    st->vals = emalloc (st->capacity * sizeof (void *));
    st->sizes = emalloc (st->capacity * sizeof (sizeKeyVal));
    st->N = 0; st->lastKeyReturned = 0;
    st->compareTo = compar;
    return (st);
}

/*-----------------------------------------------------------*/
/*
 *  freeST(ST)
 *
 *  RECEBE uma BinarySearchST  ST e devolve ao sistema toda a memoria 
 *  utilizada por ST.
 *
 */
void  
freeST(BinarySearchST st)
{
    int i;
    for (i = 0; i < st->N; i++) {
        free(st->keys[i]); 
        free(st->vals[i]);
    }
    free(st->keys); free(st->vals); free(st->sizes);
    free(st);
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
put(BinarySearchST st, const void *key, size_t nKey, const void *val, size_t nVal)
{
    if (key == NULL)
        return;
    if (val == NULL) {
        delete(st, key);
        return;
    }
    int i = rank(st, key), j;
    if (i < st->N && st->compareTo(key, st->keys[i]) == 0) {
        void *cloneVal = emalloc (nVal);
        memcpy (cloneVal, val, nVal);
        st->vals[i] = cloneVal;
        return;
    }
    if (st->N == st->capacity)
        resize(st, 2 * st->capacity);
    for (j = st->N; j > i; j--)  {
            st->keys[j] = st->keys[j-1];
            st->vals[j] = st->vals[j-1];
            st->sizes[j] = st->sizes[j - 1];
    }
    void *cloneKey = emalloc (nKey), *cloneVal = emalloc (nVal);
    memcpy (cloneKey, key, nKey); memcpy (cloneVal, val, nVal);
    st->keys[i] = cloneKey;
    st->vals[i] = cloneVal;
    st->sizes[i].sizeKey = nKey; st->sizes[i].sizeVal = nVal;
    st->N++;   
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
get(BinarySearchST st, const void *key)
{
    if (isEmpty(st) || key == NULL)
        return (NULL);
    int i = rank(st, key);
    if (i < st->N && st->compareTo(key, st->keys[i]) == 0) {
        size_t nVal = st->sizes[i].sizeVal;
        void *cloneVal = emalloc (nVal);
        memcpy (cloneVal, st->vals[0], nVal);
        return (cloneVal);
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
contains(BinarySearchST st, const void *key)
{
    if (key == NULL)
        return (FALSE);
    return (get(st, key) != NULL);
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
delete(BinarySearchST st, const void *key)
{
    if (isEmpty(st) || key == NULL)
        return;
    int i = rank(st, key), j;
    if (i == st->N || st->compareTo(key, st->keys[i]) != 0)
        return;
    for (j = i; j < st->N - 1; j++) {
        st->keys[j] = st->keys[j + 1];
        st->vals[j] = st->vals[j + 1];
        st->sizes[j] = st->sizes[j + 1];
    }
    free(st->keys[i]); free(st->vals[i]);
    st->N--;
    if (st->N > 0 && st->N == st->capacity / 4)
        resize(st, st->capacity / 2);
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
size(BinarySearchST st)
{
    return (st->N);
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
isEmpty(BinarySearchST st)
{
    return (st->N == 0);
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
min(BinarySearchST st)
{
    if (isEmpty(st))
        return (NULL);
    size_t nMin = st->sizes[0].sizeKey;
    void *cloneMin = emalloc (nMin);
    memcpy (cloneMin, st->keys[0], nMin);
    return (cloneMin);
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
max(BinarySearchST st)
{
    if (isEmpty(st))
        return (NULL);
    size_t nMax = st->sizes[st->N - 1].sizeKey;
    void *cloneMax = emalloc (nMax);
    memcpy (cloneMax, st->keys[st->N - 1], nMax);
    return (cloneMax);
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
rank(BinarySearchST st, const void *key)
{
    if (isEmpty(st) || key == NULL)
        return (NULL);
    int begin = 0, end = st->N - 1;
    while (begin <= end) {
        int mid = begin + (end - begin) / 2;
        int cmp = st->compareTo(key, st->keys[mid]);
        if (cmp < 0) 
            end = mid - 1; 
        else if (cmp > 0) 
            begin = mid + 1; 
        else 
            return (mid); 
    }
    return (begin);
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
select(BinarySearchST st, int k)
{
    if (k + 1 > st->N)
        return (NULL);
    return (st->keys[k + 1]);
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
deleteMin(BinarySearchST st)
{
    if (isEmpty(st))
        return;
    delete(st, st->keys[0]);
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
deleteMax(BinarySearchST st)
{
    if (isEmpty(st))
        return;
    delete(st, st->keys[st->N - 1]);
}

/*-----------------------------------------------------------*/
/* 
 *  KEYS(ST, INIT)
 * 
 *  RECEBE uma tabela de símbolos ST e um Bool INIT.
 *
 *  Se INIT é TRUE, KEYS() RETORNA uma cópia/clone da menor chave na ST.
 *  Se INIT é FALSE, KEYS() RETORNA a chave sucessora da última chave retornada.
 *  Se ST está vazia ou não há sucessora da última chave retornada, KEYS() RETORNA NULL.
 *
 *  Se entre duas chamadas de KEYS() a ST é alterada, o comportamento é 
 *  indefinido. 
 *  
 */
void * 
keys(BinarySearchST st, Bool init)
{
    if (isEmpty(st) || st->lastKeyReturned == st->N - 1) {
        st->lastKeyReturned = 0;
        return (NULL);
    }
    if (init)
        return (min(st));
    else {
        size_t nKey = st->sizes[st->lastKeyReturned].sizeKey;
        void *cloneKey = emalloc (nKey);
        memcpy (cloneKey, st->keys[st->lastKeyReturned++], nKey);
        return (cloneKey);
    }
}

/*-----------------------------------------------------------*/
/*
  Visit each entry on the ST.

  The VISIT function is called, in-order, with each pair key-value in the ST.
  If the VISIT function returns zero, then the iteration stops.

  visitST returns zero if the iteration was stopped by the visit function,
  nonzero otherwise.
*/
int
visitST(BinarySearchST st, int (*visit)(const void *key, const void *val))
{
    int i;
    for (i = 0; i < st->N; i++) {
        if (visit(st->keys[i], st->vals[i]) == 0)
            return (0);
    }
    return (i + 1);
}
    

/*------------------------------------------------------------*/
/* 
 * Funções administrativas
 */
void
resize(BinarySearchST st, int newCapacity)
{
    void** tempKeys = emalloc (newCapacity * sizeof (void *));
    void** tempVals = emalloc (newCapacity * sizeof (void *));
    sizeKeyVal* tempSizes = emalloc (newCapacity * sizeof (sizeKeyVal));
    int i;
    for (i = 0; i < st->N; i++) {
        tempKeys[i] = st->keys[i];
        tempVals[i] = st->vals[i];
        tempSizes[i] = st->sizes[i];
    }
    free(st->keys); free(st->vals); free(st->sizes);
    st->keys = tempKeys; st->vals = tempVals; st->sizes = tempSizes;
    st->capacity = newCapacity;
}