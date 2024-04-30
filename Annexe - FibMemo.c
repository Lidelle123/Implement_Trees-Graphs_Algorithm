#include <stdio.h>

#define MAX 100
unsigned long long fibo[MAX];

unsigned long long fibonacciM(int n) {
    if (n <= 1) {
        return n;
    }

    if (fibo[n] != 0) {
        return fibo[n];
    }

    fibo[n] = fibonacciM(n - 1) + fibonacciM(n - 2);

    return fibo[n];
}

