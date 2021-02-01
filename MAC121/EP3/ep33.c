#include <stdio.h>
#include <stdlib.h>

int posicaoMax(int *v, int n, int ini)
{/*Função que retorna em que posição do vetor, verificado a partir da posição ini, se verifica o maior inteiro.*/
    int i, max = ini;
    for (i = ini; i < n; i++) {
        if (v[i] > v[max]) max = i;
    }
    return (max);
}

int ordenado(int *v, int n)
{
    int i, ord = 1;
    for (i = 0; i < n && ord == 1; i++){
        if (i + 1 < n && v[i] < v[i + 1]) ord = 0;
    }
    return (ord);
}

void troca(int *v, int i, int j)
{
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void flip(int *v, int n, int pos)
{
    int i, j;
    for (i = pos, j = n - 1; i < j; i++, j--) troca(v, i, j);
}

void flipSort(int *v, int n)
{
    int pos = 0, posMax; 
    while (!ordenado(v, n)) {
        posMax = posicaoMax(v, n, pos);
        if (posMax != pos) {
            //if (posMax != n - 1)
            flip(v, n, posMax);
            for(i = 0; i < n; i++) printf ("%d ",v[i]);
            flip(v, n, pos);
            for(i = 0; i < n; i++) printf ("%d ",v[i]);
            printf ("%d %d ", posMax, pos);
        }
        pos++; 
    }
}

int main()
{
   int *v; 
   int i, n;
   printf ("Digite o tamanho da pilha de panquecas: "); scanf("%d", &n);
   v = malloc (n * sizeof (int));
   for (i = 0; i < n; i++) scanf("%d", &v[i]);
   printf ("\nFlips -> ");
   flipSort(v,n);
   printf ("\n");
   for(i = 0; i < n; i++) printf ("%d ",v[i]);
   free(v);
}
