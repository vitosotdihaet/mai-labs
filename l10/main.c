/* Лабораторная работа №10
 * Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>

unsigned long long mpow(unsigned long long a, unsigned long long n) {
    unsigned long long exp = 1;
    for (unsigned long long i = 1; i <= n; ++i) {
        exp *= a;
    }
    return exp;
}

int main() {
    unsigned long long a, n, answ;
    printf("Only natural numbers are allowed!\n");
    printf("Input a number you want to raise to a power:\n");
    scanf("%lld", &a);
    printf("Input a power you want to raise %lld to:\n", a);
    scanf("%lld", &n);

    answ = mpow(a, n);
    
    printf("Here is %lld to the power of %lld: %lld\n", a, n, answ);
    return 0;
}