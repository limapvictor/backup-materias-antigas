#include <stdio.h>
#include <stdlib.h>

// typedef struct {
//     int max;
//     int min; } vetor;

// vetor maxMin(int v[], int n) {
//     int max, min;
//     vetor s;
//     if (n == 1){
//         s->max = s->min = v[0];
//     }
//     max = min = maxMin(v[], n-1);
//     if(max > v[n-1]){
//         s->max = max;
//     }
//     if(min < v[n-1]){
//         s->min = min;
//     }
//     return (s);
// }

double f(double x, double y)
{
    if (x >= y){
        return ((x + y) / 2);
    }
    return (f(f(x+2, y-1), f(x+1,y-2)));
}

int fibonacci(int n)
{
    printf("*");
    if ((n == 1) || (n == 2)){
        return (1);
    }
    return (fibonacci(n-1) + fibonacci(n-2));
}

void main(void) 
{
    // int n = 4;
    // int v[4] = [1,4,8,9];
    // vetor s;
    // s = maxMin(v, n);
    printf("%f \n", f(1,10));
    int i = fibonacci(7);
}

