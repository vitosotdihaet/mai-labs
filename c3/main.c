/* Курсовой проект №3, вариант №11        */
/* Студент гр. М8О-103Б-22 Клименко В. М. */

#include <stdio.h>
#include <math.h>

unsigned long long mpow(unsigned long long a, unsigned long long n) {
    unsigned long long exp = 1;
    for (unsigned long long i = 1; i <= n; ++i) {
        exp *= a;
    }
    return exp;
}

long double f_factorial(long double a) {
    long double answ = 1;
    for (long double i = 1; i <= a; ++i) {
        answ *= i;
    }
    return answ;
}

long double taylor(long double x, unsigned long long n) {
    long double k = 1, eps = 1, sum = 0;
    for (unsigned long long i = 0; i <= n; ++i) {
        sum += pow(-1, i) * (2 * pow(i, 2) + 1) / f_factorial(2 * i) * pow(x, 2 * i);
    }
    return sum;
}

int main() {
    unsigned long long n_t = 10;
    long double n = 10;
    long double a = 0.1, b = 0.6, dx = (b - a)/n, x = a - dx;

    printf("x         taylor's row  c function   taylor iterations\n");

    for (int i = 0; i <= n; ++i) {
        x += dx;
        printf("%Lf  ", x);
        printf("%Lf      ", taylor(x, n_t));
        printf("%Lf     ", (1 - x * x/2) * cos(x) - x/2 * sin(x));
        printf("%lld", n_t);
        printf("\n");
    }

    return 0;
}