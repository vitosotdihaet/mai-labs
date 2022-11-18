/* Лабораторная работа №11 вариант №30    */
/* Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>
#include <ctype.h>
#include "string.h"

int main() {
    int END = 0;
    int t = 0;
    int n = 0;
    char lc = ' ';
    string num;

    init_string(&num);

    while (1) {
        free_string(&num);
        END = read_string(&num, &t, &n, &lc);
        if (END == 1) break;
        if (!(t == 0 && atoll(num.values) <= __INT_MAX__)) {
            printf("%s%c", num.values, lc);
        } else {
            printf("%c", lc);
        }
        if (n == 1) printf("\n");
    }
    printf("End of programm...\n");

    return 0;
}
