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

int main()
{
    int *c;
    int a[] = {2,3,4,7,8}, b[] = {1,3,6,8,9}, v[] = {2,26,6345,63,234,23,26};
    c = merge(a, b, 5, 5);
    countSort(v,7);
}