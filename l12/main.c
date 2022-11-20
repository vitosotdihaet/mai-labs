/* Лабораторная работа №12 вариант №30    */
/* Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long mpow(unsigned long long a, unsigned long long n) {
    unsigned long long exp = 1;
    for (unsigned long long i = 1; i <= n; ++i) {
        exp *= a;
    }
    return exp;
}

long long solve(long long n) {
    // long long answ = 0;
    long long l = (long long) log10((double) abs(n)) + 1;
    int n1, n2;
    short otr = -1;
    if (n < 0) {
        n = -n;
        otr = 1;
    }

    for (int i = 0; i < l - 1; i += 2) {
        n1 = n / mpow(10, i) % 10;
        n2 = n / mpow(10, i + 1) % 10;
        printf("i = %d:\nn1 = %d, n2 = %d\n", i, n1, n2);
        if (n1 < n2) {
            n -= n1 * mpow(10, i);
            n -= n2 * mpow(10, i + 1);
            n += n2 * mpow(10, i);
            n += n1 * mpow(10, i + 1);
        }
    }

    return n * -1 * otr;
}

int main() {
    int END = 0;
    long long inp = 0;
    long long out = 0;

    while (1) {
        END = scanf("%lld", &inp);
        if (END == -1) break;
        out = solve(inp);
        printf("%lld\n", out);

    }

    printf("End of programm...\n");
    return 0;
}
