#include "set.h"

unsigned long long mpow(unsigned long long a, unsigned long long n) {
    unsigned long long exp = 1;
    for (unsigned long long i = 1; i <= n; ++i) {
        exp *= a;
    }
    return exp;
}

unsigned long long int_to_bin(unsigned long long a) {
    unsigned long long answ = 0, i = 0;
    while (a != 0) {
        answ += (a % 2 * mpow(10, i));
        ++i;
        a /= 2;
    }
    return answ;
}

void print_bin(unsigned long long a) {
    if (a != 0) {
        print_bin(a / 2);
    }
    printf("%lld", a % 2);
}

int main() {
    set s;
    init_set(&s);
    int read = read_set(&s);

    while (read != EOF) {
        printf("Count of repeated letters: %d\n", read);
        printf("Set as binary: ");
        print_bin(s.set);
        printf("\n");
        printf("Size of set: %d\n\n", set_size(&s));
        init_set(&s);
        read = read_set(&s);
    }
    printf("End of programm...\n");

    return 0;
}