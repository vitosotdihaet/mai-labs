/* Лабораторная работа №12 вариант №30    */
/* Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>

#define ENOUGH ((CHAR_BIT * sizeof(int) - 1) / 3 + 2);

short is_split(char c) {
    return (c == ' ' || c == ',' || c == '\n' || c == '\t');
}

unsigned long long change_number(unsigned long long a) {
    unsigned long long answ  = 0;
    char str[ENOUGH(a)];
}

int main() {
    unsigned long long number = 0;
    int last_a = 0;
    char c;

    while (1) {
        c = getchar();
        if (c == EOF) { break; }
        switch (last_a) {
            case 0:
                if (is_split(c)) {
                    last_a = -1;
                } else {
                    last_a = 1;
                    number = number * 10 + (int) (c - '0');
                }
                break;
            case -1:
                printf("%lld\n", change_num(number));
                number = 0;
                break;
        }
    }

    return 0;
}