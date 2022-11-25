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

int main() {
    set s;
    init_set(&s);

    printf("Count of repeated letters: %d\n", read_set(&s));
    printf("Set as binary: %lld\n", int_to_bin(s.set));
    printf("Size of set: %d\n", set_size(&s));

    return 0;
}