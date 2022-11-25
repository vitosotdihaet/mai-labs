#ifndef SET_H

#define SET_H

#include <stdio.h>
#include <stdlib.h>

typedef struct set {
    unsigned long long set;
} set;

void init_set(set* s);

int char_to_set(set* s, char c);

int read_set(set* s);

int set_size(set* s);

#endif