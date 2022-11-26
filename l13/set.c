#include "set.h"

const unsigned long long _vowels = ~((1 << ('a' - 'a')) | (1 << ('e' - 'a')) | (1 << ('i' - 'a')) | (1 << ('o' - 'a')) | (1 << ('u' - 'a')));

void init_set(set* s) {
    s->set = 0;
}

void print_missing_chars(set s) {
    unsigned long long a = s.set;
    int off = 0;

    while (a != 0) {
        if (a % 2 == 0) {
            printf("%c ", off + 'a');
        }
        a /= 2;
        ++off;
    }

    printf("\n");
}

int char_to_set(set* s, char c) {
    unsigned long long pre = s->set; 
    if (c < 'a' || c > 'z') {
        return -1;
    }

    s->set = s->set | (1 << (c - 'a'));
    if (pre == s->set) {
        return 0;
    }
    return 1;
}

int read_set(set* s) {
    char c;
    int end = 0;
    while (1) {
        c = getchar();
        if (c == ' ' || c == ',' || c == '\t' || c == '\n') {
            if (c == '\n') return -2;
            break;
        } else if ((int) c == EOF) {
            end = EOF;
            break;
        }
        end += (1 - char_to_set(s, c)) % 2;
    }

    return end;
}

int set_size(set* s) {
    unsigned long long a = s->set;
    int answ = 0;
    while (a != 0) {
        answ += a % 2;
        a /= 2;
    }

    return answ;
}

set set_intersection(set s1, set s2) {
    return set_from(s1.set & s2.set);
}

set set_unification(set s1, set s2) {
    return set_from(s1.set | s2.set);
}

set set_from(unsigned long long a) {
    set s;
    init_set(&s);
    s.set = a;
    return s;
}
