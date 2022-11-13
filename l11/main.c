/* Лабораторная работа №11 вариант №30    */
/* Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>
#include "string.h"


int read_string(string* s) {
    char c = ' ';
    int end = 0;

    while (1) {
        c = getchar();
        if (c == ' ' || c == ',' || c == '\t' || c == '\n') {
            break;
        } else if ((int) c == EOF) {
            end = 1;
            break;
        }
        add_char(s, c);
        // printf("%ld\n", s->memory_size);
        // printf("%s\n", s->values);
    }

    return end;
}


int main() {
    int END = 0;
    string num;

    init_string(&num);

    while (!END) {
        free_string(&num);
        END = read_string(&num);
        // if (compare(num, int_max)) {
        if (atoll(num.values) <= __INT_MAX__) {
            printf("%s\n", num.values);
        }
    }

    return 0;
}
