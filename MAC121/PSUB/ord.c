#include <stdio.h>
#include <stdlib.h>

void print(int *v, int n)
{
    for (int i = 0; i < n; i++) printf ("%d ",v[i]);
    printf("\n");
}

void troca(int *v, int i, int j)
{
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void insercaoSort(int *v, int n)
{
    int b, i, x;
    for (b = 1; b < n; b++) {
        x = v[b];
        for (i = b - 1; i >= 0 && v[i] > x; i--) v[i + 1] = v[i];
        v[i + 1] = x;
        print(v,n);
    }
}

void ordenaDois(int *v, int n)
{
    int i = -1, pivo = v[n - 1], j;
    for (j = 0; j < n; j++) {
        if (v[j] < pivo) {
            i++;
            troca(v, i, j);
        } else {
            pivo = v[j];
        }
    }
}


int *merge(int *a, int *b, int m, int n)
{
    int *c;
    int i = 0, j = 0, k = 0;
    c = malloc ((m + n) * sizeof (int));
    while(i < m && j < n) {
        if (a[i] < b[j]){
            c[k] = a[i];
            i++;
        } else {
            c[k] = b[j];
            j++;
        }
        k++;
    }
    while (i < m) c[k++] = a[i++];
    while (j < n) c[k++] = b[j++];
    return (c);
}

void mergeRec(int *a, int *b, int m, int n, int *c, int pos)
{
    if (m == 0 && n == 0) return;
    if (n == 0) {
        c[pos] = a[m - 1];
        mergeRec(a, b, m - 1, n, c, pos - 1); return;
    }
    if (m == 0){
        c[pos] = b[n - 1];
        mergeRec(a, b, m, n - 1, c, pos - 1); return;
    }
    if (a[m - 1] > b[n - 1])
        c[pos] = a[--m];
    else
        c[pos] = b[--n];
    mergeRec(a, b, m, n, c, pos - 1);
}

void countSort(int *V, int n)
{
    int *cont;
    int i,j,k;
    cont = malloc (n * sizeof (int));    
    for (i = 0; i <n; i++) cont[i] = 0;
    for (i=0; i< n; i++){
        for (j = 0; j < n; j++){
            if (V[j] < V[i]) cont[i]++;        
        }
        troca(V, i, cont[i]);
        // if (i != cont[i] && V[cont[i]] == V[i]){
        //     for (k = cont[i] + 2; k < i; k++) V[k + 1] = V[k];
        //     V[cont[i] + 1] = V[cont[i]];
        // }
    }
    print(V, n);
}

void rebaixa(int v[], int n, int i)
{
    int pai, filho;
    pai = i; filho = 2 * i + 1;
    while (filho < n) {
        if (filho + 1 < n && v[filho + 1] > v[filho])
            filho++;
        if (v[filho] < v[pai])
            break;
        else {
            troca(v, pai, filho);
            pai = filho;
            filho = 2 * pai + 1;
        }
    }
}

void heapifica(int v[], int n)
{
    int i;
    for(i = (n - 2) / 2; i >= 0; i--) {
        rebaixa(v, n, i);
        print(v, n);
    }
}

int main()
{
    int a[] = {2,3,4,7,8, 11}, b[] = {1,3,6,8,9}, v[] = {2,26,6345,63,234,23,26};
    int c[11] = {5, 4, 4, 5, 4, 5, 5, 4, 5, 4, 5};
    int h[] = {12, 23, 5, 9, 19, 0, 24, 4, 1, 13, 21, 2, 7, 14, -9, 10, 14};
    heapifica(h, 17);
}