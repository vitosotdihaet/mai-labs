#ifndef SET_H

#define SET_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned long long set;
} set;

void init_set(set* s);

void print_missing_chars(set s);

int char_to_set(set* s, char c);

int read_set(set* s);

int set_size(set* s);

set set_unification(set s1, set s2);

set set_intersection(set s1, set s2);

set set_from(unsigned long long a);

#endif
