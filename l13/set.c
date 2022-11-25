#include "set.h"

void init_set(set* s) {
    s->set = 0;
}

int char_to_set(set* s, char c) {
    unsigned long long pre = s->set, off; 
    if (c < 'a') {
        return -1;
    } else if (c <= 'z') {
        off = 'a';
    // } else if (c < 'а') { // russian a
    //     return -1;
    // } else if (c <= 'я') {
    //     off = 'а';
    //     // off = 'a';
    } else {
        return -1;
    }

    s->set = s->set | (1 << (c - off));
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
            break;
        } else if ((int) c == EOF) {
            end = EOF;
            break;
        }
        end += 1 - char_to_set(s, c);
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
