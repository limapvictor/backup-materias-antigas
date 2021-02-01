#include <stdio.h>
#include <stdlib.h>

int conjecturaCollatz(int n, int ini, int fim, int vetorPassos[])
{
    int passos, i;
    passos = 0;
    while(n != 1){
        if(ini <= n <= fim && vetorPassos[n - ini] != 0){
            passos = passos + vetorPassos[n - ini];
            return(passos);
        }else{
            if(n % 2 == 0){
                n = n / 2;
            }else{
                n = (3 * n) + 1;
            }
            passos ++;
        }
    }
    return(passos);
}

void main(void)
{
    int ini, fim, i, passos;
    printf("Insira o inicio do intervalo: ");
    scanf("%d",&ini);
    printf("Insira o final do intervalo: ");
    scanf("%d",&fim);
    int vetorPassos[fim - ini];
    for(i = ini; i <= fim; i++){
        vetorPassos[i - ini] = 0;
    }
    // vetorPassos = (int *)calloc(fim - ini + 1,sizeof(int));
    for(i = ini; i <= fim; i++){
        passos = conjecturaCollatz(i, ini, fim, vetorPassos);
        vetorPassos[i - ini] = passos;
        printf("O numero %d realizou %d passos \n", i, passos);
    }
    free(vetorPassos);
}

