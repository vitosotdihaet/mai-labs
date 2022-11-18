/* Лабораторная работа №12 вариант №30    */
/* Студент гр. М8О-103Б-22 Клименко В. М. */
#include <stdio.h>
#include <string.h>
#include "string.h"

void solve(string* s) {
    char t1, t2;
    reverse_string(s);
    for (unsigned long i = 0; i < s->last_element - s->last_element % 2; i += 2) {
        t1 = s->values[i];
        t2 = s->values[i + 1];
        if (t2 == '-') continue;
        if (t1 - '0' < t2 - '0') {
            s->values[i] = t2;
            s->values[i + 1] = t1;
        } 
    }
    reverse_string(s);
}

int main() {
    int END = 0;
    string inp;

    init_string(&inp);

    while (1) {
        init_string(&inp);
        END = read_string(&inp);
        if (END) break;
        solve(&inp);
        printf("Number after processing: %s\n", inp.values);
    }

    printf("End of programm...\n");
    return 0;
}
