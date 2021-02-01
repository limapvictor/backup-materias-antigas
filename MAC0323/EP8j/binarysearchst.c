/*
 * MAC0323 Estruturas de Dados e Algoritmo II
 * 
 * Tabela de simbolos implementada atraves de vetores ordenados 
 * redeminsionaveis 
 *
 *     https://algs4.cs.princeton.edu/31elementary/BinarySearchST.java.html
 * 
 * As chaves e valores desta implementaÃ§Ã£o sÃ£o mais ou menos
 * genÃ©ricos
 */

/* interface para o uso da funcao deste mÃ³dulo */
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
 * FunÃ§Ãµes administrativas
 */

/*----------------------------------------------------------*/
/* 
 * Estrutura BÃ¡sica da Tabela de SÃ­mbolos: 
 * 
 * implementaÃ§Ã£o com vetores ordenados
 */
typedef struct bytes {
    int nkey;
    int nval;
} nbytes;
struct binarySearchST {
    void** keys;
    void** vals;
    int tam;
    int n;
    int (*comp) (const void *, const void *);
    nbytes* bit;
    int atual;
};

/*-----------------------------------------------------------*/
/*
 *  initST(COMPAR)
 *
 *  RECEBE uma funÃ§Ã£o COMPAR() para comparar chaves.
 *  RETORNA (referÃªncia/ponteiro para) uma tabela de sÃ­mbolos vazia.
 *
 *  Ã‰ esperado que COMPAR() tenha o seguinte comportamento:
 *
 *      COMPAR(key1, key2) retorna um inteiro < 0 se key1 <  key2
 *      COMPAR(key1, key2) retorna 0              se key1 == key2
 *      COMPAR(key1, key2) retorna um inteiro > 0 se key1 >  key2
 * 
 *  TODAS OS OPERAÃ‡Ã•ES da ST criada utilizam a COMPAR() para comparar
 *  chaves.
 * 
 */
BinarySearchST
initST(int (*compar)(const void *key1, const void *key2))
{
    BinarySearchST st;
    int i;
    if (compar == NULL) return NULL;
    st = emalloc(sizeof(struct binarySearchST));
    st->tam = 2;
    st->keys = emalloc(st->tam*sizeof(void*));
    st->vals = emalloc(st->tam*sizeof(void*));
    st->bit = emalloc(st->tam*sizeof(nbytes));
    for (i = 0; i<st->tam; i++){
        st->keys[i] = NULL; st->vals[i] = NULL;
        st->bit[i].nval = 0; st->bit[i].nkey = 0;
    }
    st->n = 0;
    st->comp = compar;
    st->atual = 0;
    return st;
}

/*-----------------------------------------------------------*/
void
resize(BinarySearchST st, int cap)
{
    void** newkeys = emalloc(cap*sizeof(void*));
    void** newvals = emalloc(cap*sizeof(void*));
    nbytes* newbit = emalloc(cap*sizeof(nbytes));
    int i;
    for (i = 0; i<cap; i++){
        newkeys[i] = NULL; newvals[i] = NULL;
        newbit[i].nkey = 0; newbit[i].nval = 0;
    }
    for (i = 0; i< st->n; i++){
        newkeys[i] = st->keys[i];
        newvals[i] = st->vals[i];
        newbit[i] = st->bit[i];
    }
    st->keys = newkeys;
    st->vals = newvals;
    st->bit = newbit;
    st->tam = cap;
    return;
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
    int i = 0;
    for (i=0; i<st->tam;i++){
        free(st->keys[i]);
        free(st->vals[i]);
    }
    free(st->keys);
    free(st->vals);
    free(st->bit);
    free(st);
}

/*------------------------------------------------------------*/
/*
 * OPERAÃ‡Ã•ES USUAIS: put(), get(), contains(), delete(),
 * size() e isEmpty().
 */

/*-----------------------------------------------------------*/
/*
 *  put(ST, KEY, NKEY, VAL, NVAL)
 * 
 *  RECEBE a tabela de sÃ­mbolos ST e um par KEY-VAL e procura a KEY na ST.
 *
 *     - se VAL Ã© NULL, a entrada da chave KEY Ã© removida da ST  
 *  
 *     - se KEY nao e' encontrada: o par KEY-VAL Ã© inserido na ST
 *
 *     - se KEY e' encontra: o valor correspondente Ã© atualizado
 *
 *  NKEY Ã© o nÃºmero de bytes de KEY e NVAL Ã© o nÃºmero de bytes de NVAL.
 *
 *  Para criar uma copia/clone de KEY Ã© usado o seu nÃºmero de bytes NKEY.
 *  Para criar uma copia/clode de VAL Ã© usado o seu nÃºmero de bytes NVAL.
 *
 */
void  
put(BinarySearchST st, const void *key, size_t nKey, const void *val, size_t nVal)
{
    int i, j;
    if (key == NULL){
        printf("Key in put() is NULL");
        return;
    }
    if (val == NULL){
        delete(st, key);
        return;
    }
    i = rank(st, key);
    if (i < st->n && st->comp(st->keys[i],key) == 0){
        st->vals[i] = emalloc(nVal);
        memcpy(st->vals[i], val, nVal);
        st->bit[i].nval = nVal;
        return;
    } 
    if (st->n == st->tam) resize(st, 2*st->tam);
    for (j = st->n; j>i; j--){
        st->keys[j] = emalloc(8);
        st->keys[j] = st->keys[j-1];
        st->vals[j] = st->vals[j-1];
        st->bit[j] = st->bit[j-1];
    }
    st->vals[i] = emalloc(nVal);
    memcpy(st->vals[i], val, nVal);
    st->bit[i].nval = nVal;
    st->keys[i] = emalloc(nKey);
    memcpy(st->keys[i], key, nKey);
    st->bit[i].nkey = nKey;
    st->n++;
}    

/*-----------------------------------------------------------*/
/*
 *  get(ST, KEY)
 *
 *  RECEBE uma tabela de sÃ­mbolos ST e uma chave KEY.
 *
 *     - se KEY estÃ¡ em ST, RETORNA NULL;
 *
 *     - se KEY nÃ£o estÃ¡ em ST, RETORNA uma cÃ³pia/clone do valor
 *       associado a KEY.
 * 
 */
void *
get(BinarySearchST st, const void *key)
{
    int i;
    if(key == NULL){
        printf("Key in get() is NULL");
        return NULL;
    }
    if(isEmpty(st) == TRUE) return NULL;
    i = rank(st, key);
    if (i < st->n && st->comp(st->keys[i], key) == 0){
        int aux = st->bit[i].nval;
        void* item = emalloc(aux);
        memcpy(item, st->vals[i], aux);  
        return item;
    }
    return NULL;
}

/*-----------------------------------------------------------*/
/* 
 *  CONTAINS(ST, KEY)
 *
 *  RECEBE uma tabela de sÃ­mbolos ST e uma chave KEY.
 * 
 *  RETORNA TRUE se KEY estÃ¡ na ST e FALSE em caso contrÃ¡rio.
 *
 */
Bool
contains(BinarySearchST st, const void *key)
{
    if (key == NULL){
        printf("Key in contains() is NULL!");
        return FALSE;
    }
    return (get(st, key) != NULL);
}

/*-----------------------------------------------------------*/
/* 
 *  DELETE(ST, KEY)
 *
 *  RECEBE uma tabela de sÃ­mbolos ST e uma chave KEY.
 * 
 *  Se KEY estÃ¡ em ST, remove a entrada correspondente a KEY.
 *  Se KEY nÃ£o estÃ¡ em ST, faz nada.
 *
 */
void
delete(BinarySearchST st, const void *key)
{
    int i, j;
    if (key == NULL) {
        printf("Key in delete() is NULL!");
        return;
    }
    if (isEmpty(st) == TRUE) return;
    i = rank(st, key);
    if(i == st->n || st->comp(st->keys[i], key) != 0) return;
    for (j = i; j<st->n-1; j++){
        st->keys[j] = st->keys[j+1];
        st->vals[j] = st->vals[j+1];
        st->bit[j] = st->bit[j+1];
    }
    st->n--;
    st->keys[st->n] = NULL;
    st->vals[st->n] = NULL;
    st->bit[st->n].nkey = 0;
    st->bit[st->n].nval = 0;
    if (st->n > 0 && st->n == st->tam/4) resize(st, st->tam/2);
    return;
}

/*-----------------------------------------------------------*/
/* 
 *  SIZE(ST)
 *
 *  RECEBE uma tabela de sÃ­mbolos ST.
 * 
 *  RETORNA o nÃºmero de itens (= pares chave-valor) na ST.
 *
 */
int
size(BinarySearchST st)
{
    return st->n;
}

/*-----------------------------------------------------------*/
/* 
 *  ISEMPTY(ST, KEY)
 *
 *  RECEBE uma tabela de sÃ­mbolos ST.
 * 
 *  RETORNA TRUE se ST estÃ¡ vazia e FALSE em caso contrÃ¡rio.
 *
 */
Bool
isEmpty(BinarySearchST st)
{
    return size(st) == 0;
}


/*------------------------------------------------------------*/
/*
 * OPERAÃ‡Ã•ES PARA TABELAS DE SÃMBOLOS ORDENADAS: 
 * min(), max(), rank(), select(), deleteMin() e deleteMax().
 */

/*-----------------------------------------------------------*/
/*
 *  MIN(ST)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e RETORNA uma cÃ³pia/clone
 *  da menor chave na tabela.
 *
 *  Se ST estÃ¡ vazia RETORNA NULL.
 *
 */
void *
min(BinarySearchST st)
{
    int aux;
    void* item;
    if (isEmpty(st) == TRUE) return NULL;
    aux = st->bit[0].nkey;
    item = emalloc(aux);
    memcpy(item, st->keys[0], aux);  
    return item;
}

/*-----------------------------------------------------------*/
/*
 *  MAX(ST)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e RETORNA uma cÃ³pia/clone
 *  da maior chave na tabela.
 *
 *  Se ST estÃ¡ vazia RETORNA NULL.
 *
 */
void *
max(BinarySearchST st)
{
    int aux;
    void* item;
    if (isEmpty(st) == TRUE) return NULL;
    aux = st->bit[st->n-1].nkey;
    item = emalloc(aux);
    memcpy(item, st->keys[st->n-1], aux);  
    return item;
}

/*-----------------------------------------------------------*/
/*
 *  RANK(ST, KEY)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e uma chave KEY.
 *  RETORNA o nÃºmero de chaves em ST menores que KEY.
 *
 *  Se ST estÃ¡ vazia EXIT_FAILURE.
 *
 */
int
rank(BinarySearchST st, const void *key)
{
    int ini, fim;
    if (key == NULL){
        printf("Key in rank() is NULL!");
        return EXIT_FAILURE;
    }
    ini = 0; fim = st->n-1;
    while (ini <= fim){
        int meio = ini + (fim - ini) / 2;
        int cmp = st->comp(key, st->keys[meio]);
        if (cmp < 0) fim = meio - 1;
        else if (cmp > 0) ini = meio + 1;
        else return meio;
    }
    return ini;
} 

/*-----------------------------------------------------------*/
/*
 *  SELECT(ST, K)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e um inteiro K >= 0.
 *  RETORNA a (K+1)-Ã©sima menor chave da tabela ST.
 *
 *  Se ST nÃ£o tem K+1 elementos RETORNA NULL.
 *
 */
void *
select(BinarySearchST st, int k)
{
    int aux;
    void* item;
    if (isEmpty(st) == TRUE) return NULL;
    if (k < 0 || k >= st->n){
        printf("k = %d in select() is invalid!", k);
        return NULL;
    }
    aux = st->bit[k].nkey;
    item = emalloc(aux);
    memcpy(item, st->keys[k], aux);  
    return item;
}

/*-----------------------------------------------------------*/
/*
 *  deleteMIN(ST)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e remove a entrada correspondente
 *  Ã  menor chave.
 *
 *  Se ST estÃ¡ vazia, faz nada.
 *
 */
void
deleteMin(BinarySearchST st)
{
    if (isEmpty(st) == TRUE){
        printf("The table is empty.");
        return;
    }
    delete(st, min(st));
    return;
}

/*-----------------------------------------------------------*/
/*
 *  deleteMAX(ST)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e remove a entrada correspondente
 *  Ã  maior chave.
 *
 *  Se ST estÃ¡ vazia, faz nada.
 *
 */
void
deleteMax(BinarySearchST st)
{
    if (isEmpty(st) == TRUE){
        printf("The table is empty.");
        return;
    }
    delete(st, max(st));
    return;
}

/*-----------------------------------------------------------*/
/* 
 *  KEYS(ST, INIT)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e um Bool INIT.
 *
 *  Se INIT Ã© TRUE, KEYS() RETORNA uma cÃ³pia/clone da menor chave na ST.
 *  Se INIT Ã© FALSE, KEYS() RETORNA uma cÃ³pia/clone da chave sucessora da Ãºltima chave retornada.
 *  Se ST estÃ¡ vazia ou nÃ£o hÃ¡ sucessora da Ãºltima chave retornada, KEYS() RETORNA NULL.
 *
 *  Se entre duas chamadas de KEYS() a ST Ã© alterada, o comportamento Ã© 
 *  indefinido. 
 *  
 */
void * 
keys(BinarySearchST st, Bool init)
{
    int aux;
    void* item;
    if (isEmpty(st) == TRUE || st->atual == st->n) return NULL;
    if (init == TRUE) {
        aux = st->bit[0].nkey;
        item = emalloc(aux);
        memcpy(item, st->keys[0], aux);  
        st->atual = 1;
    }
    else{
        aux = st->bit[st->atual].nkey;
        item = emalloc(aux);
        memcpy(item, st->keys[st->atual], aux);  
        st->atual++;
    }
    return item;
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
    for (i = 0; i<st->n; i++){
        int stops;
        stops = visit(st->keys[i], st->vals[i]);
        if (stops == 0) return 0;
    }
    return 1;
}
    

/*------------------------------------------------------------*/
/* 
 * FunÃ§Ãµes administrativas
 */
