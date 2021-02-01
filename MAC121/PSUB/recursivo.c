#include <stdio.h>
#include <stdlib.h>

void maxMin(int v[], int n, int i, int *res)
{
    if (i < n) {
        int max = res[0], min = res[1];
        if (v[i] > max) res[0] = v[i];
        if (v[i] < min) res[1] = v[i];
        maxMin(v, n, i + 1, res);
    }
}

int fibonacci(int n)
{
    printf("*");
    if ((n == 1) || (n == 2))
        return (1);
    return (fibonacci(n-1) + fibonacci(n-2));
}

int digito(int n)
{
    if (n < 10)
        return (1);
    return (1 + digito(n / 10));
}

int ackerman(int m, int n)
{
    if (m == 0) return (n + 1);
    if (n == 0) return (ackerman(m - 1, 1));
    return (ackerman((m - 1), ackerman(m, n - 1)));
}

int euclides(int m, int n)
{
    if ((m % n) == 0)
        return (n);
    return euclides(n, m % n);
}

void trocaParImpar(int A[], int inic, int fim)
{
    int aux;
    while (A[fim] % 2 == 0 && inic < fim)
        fim --;
    while (A[inic] % 2 == 1 && inic < fim)
        inic++;
    if (inic < fim){
        aux = A[inic];
        A[inic] = A[fim];
        A[fim] = aux;
        trocaParImpar(A, inic, fim);
    }
}

int fusc(int n)
{
    if (n <= 1)
        return (1);
    if (n % 2 == 0)
        return( fusc(n / 2) );
    return( fusc((n-1)/2) + fusc((n+1)/2) );
}

int zzz(int n)
{
    int aux;
    if (n <= 2)
        return(1);
    n--;
    aux = zzz(n);
    n--;
    return (aux + zzz(n));
}

void quatrocores(int **mapa, int n, int *cores, int atual)
{
    if (atual == n) return;
    
}

int main()
{
    int v[] = {1, 4, 7, 3, 16, 15, -3, -62, -7, 15, -7}, res[] = {-999999, 99999999}, n = 11;
    int A[] = {8,10,3,6,5,2,9,1,4}, fim = 8;
    int m = 2;
    printf("zzz = %d\n", zzz(m));
}