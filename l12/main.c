/* Лабораторная работа №12 вариант №30    */
/* Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

long long answ(char s[], long long l) {
    char *_s = (char*) calloc(l, l * sizeof(char));
    // printf("%s\n", s);
    for (long long i = 0; i < l; ++i) {
        _s[i] = s[l - i - 1];
    }
    // printf("%s\n", _s);
    return atoll(_s);
}

unsigned long long mpow(unsigned long long a, unsigned long long n) {
    unsigned long long exp = 1;
    for (unsigned long long i = 1; i <= n; ++i) {
        exp *= a;
    }
    return exp;
}

long long solve(long long s) {
    long long l = (long long) log10((double) abs(s)) + 1;
    long long ns = 0;
    if (s < 0) {
        printf("-");
        s = -s;
    }
    for (long long i = l - 1; i > -1; --i) {
        // printf("at i = %lld: %d - %c\n", i + off, (s / mpow(10, i)) % 10, (s / mpow(10, i)) % 10 + '0');
        str[i] = (s / mpow(10, i)) % 10 + '0';
        // printf("%c\n", t1[l - i - 1]);
    }
    // printf("%s\n", str);

    // for (long long i = 0; i < l - l % 2; i += 2) {
    //     t1 = ns / mpow(10, i);
    //     t2 = str[i + 1];
    //     if (t2 == '-') continue;
    //     if (t1 < t2) {
    //         str[i] = t2;
    //         str[i + 1] = t1;
    //     } 
    // }
    return 
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
