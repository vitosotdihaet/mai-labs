/* Лабораторная работа №11 вариант №30    */
/* Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>
#include "string.h"


int main() {
    int END = 0;
    string num;

    init_string(&num);

    while (1) {
        free_string(&num);
        END = read_string(&num);
        if (END) break;
        if (atoll(num.values) <= __INT_MAX__) {
            printf("This number is less than INT_MAX! Delete!\n");
        } else {
            printf("This number is greater than INT_MAX! Remain %s!\n", num.values);
        }
    }
    printf("End of programm...\n");

    return 0;
}
