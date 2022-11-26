/* Лабораторная работа №13, вариант 13    */
/* Студент гр. М8О-103Б-22 Клименко В. М. */

#include "set.h"

const unsigned long long vowels = ((1 << ('a' - 'a')) | (1 << ('e' - 'a')) | (1 << ('i' - 'a')) | (1 << ('o' - 'a')) | (1 << ('u' - 'a')));

unsigned long long mpow(unsigned long long a, unsigned long long n) {
    unsigned long long exp = 1;
    for (unsigned long long i = 1; i <= n; ++i) {
        exp *= a;
    }
    return exp;
}

void print_bin(unsigned long long a) {
    if (a != 0) {
        print_bin(a / 2);
    }
    printf("%lld", a % 2);
}

int main() {
    set current_set, answer_set, temp;
    init_set(&current_set);
    init_set(&answer_set);
    init_set(&temp);

    printf("Input words:\n");
    int read = 0;

    while (read != EOF) {        
        init_set(&current_set);
        read = read_set(&current_set);

        answer_set = set_unification(answer_set, current_set);
        if (read == -2) {
            temp = set_unification(set_intersection(answer_set, set_from(vowels)), set_from(~vowels));
            if (temp.set != -1) {
                printf("Vowels that are not presented in these words: ");
                print_missing_chars(temp);
            } else {
                printf("All the vowels were presented in these words\n");
            }
            init_set(&answer_set);
        }
    }
    printf("End of programm...\n");

    return 0;
}
