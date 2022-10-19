/* Лабораторная работа №8
 * Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>

int main() {
    unsigned long long a, exp = 1;
    printf("Input a power of 2:\n");
    scanf("%lld", &a);
    for (unsigned long long i = 1; i <= a; ++i) {
        exp *= 2;
    }
    printf("Here is 2 to the power of %lld: %lld\n", a, exp);
    return 0;
}