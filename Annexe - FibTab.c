#include <stdio.h>

#define MAX 100
unsigned long long fibo[MAX];


unsigned long long fibonacciT(int n) {
    if (n <= 1) {
        return n;
    }

    // Création d'un tableau pour stocker les résultats intermédiaires
    fibo[0] = 0;
    fibo[1] = 1;

    // Calcul de la suite de Fibonacci
    for (int i = 2; i <= n; ++i) {
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    }
    

    return fibo[n];
}
