#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define STRING_KEY_CAP 28


typedef struct {
    char key_s[STRING_KEY_CAP];
    int key_int;
} complex_key;

typedef struct {
    complex_key key;
    char *value;
} item;

typedef struct {
    item *rows;
    uint64_t count;
} table;


table table_alloc();

table table_copy(table t);
void table_push(table *t, char *key_s, int key_int, char *value);
table table_quick_sort(table t);

char *table_binary_search(table t, char *key_s, int key_int);

void table_print(table t);

void table_dealloc(table *t);


#endif // TABLE_H



#ifdef TABLE_IMPLEMENTATION

table table_alloc() {
    table t;
    t.rows = (item*) calloc(0, sizeof(item));
    t.count = 0;
    return t;
}


table table_copy(table t) {
    table temp = table_alloc();

    for (uint64_t i = 0; i < t.count; ++i) {
        char *value = (char*) calloc(256, sizeof(char));
        strcpy(value, t.rows[i].value);
        table_push(&temp, t.rows[i].key.key_s, t.rows[i].key.key_int, value);
    }

    return temp;
}

void table_push(table *t, char *key_s, int key_int, char *value) {
    complex_key ck = {
        .key_int = key_int
    };

    for (int i = 0; i < STRING_KEY_CAP && i < (int) strlen(key_s); ++i) {
        ck.key_s[i] = key_s[i];
    }

    item i = {
        .key = ck,
        .value = value
    };

    t->rows = (item*) realloc(t->rows, sizeof(item) * (t->count + 1));
    t->count++;

    t->rows[t->count - 1] = i;
}

void _table_quick_sort(table *t, uint64_t l, uint64_t r) {
    char *pivot_value = t->rows[l].value;
    complex_key pivot_key = t->rows[l].key;
    uint64_t l_init = l, r_init = r;

    while (l < r) {
        while (strcmp(pivot_value, t->rows[r].value) <= 0 && (l < r)) r--;
        if (l != r) {
            t->rows[l].value = t->rows[r].value;
            t->rows[l].key = t->rows[r].key;
            l++;
        }

        while (strcmp(pivot_value, t->rows[l].value) > 0 && (l < r)) l++;

        if (l != r) {
            t->rows[r].value = t->rows[l].value;
            t->rows[r].key = t->rows[l].key;
            r--;
        }
    }

    t->rows[l].key = pivot_key;
    t->rows[l].value = pivot_value;

    uint64_t pivot = l;
    l = l_init;
    r = r_init;

    if (l < pivot) _table_quick_sort(t, l, pivot - 1);
    if (r > pivot) _table_quick_sort(t, pivot + 1, r);
}

// sort keys by elements
table table_quick_sort(table t) {
    table temp = table_copy(t);

    _table_quick_sort(&temp, 0, temp.count - 1);

    return temp;
}


char *table_binary_search(table t, char *key_s, int key_int) {
    char *answ = NULL;
    uint64_t l = 0, r = t.count, m = (l + r)/2;

    // bs in t.rows

    return answ;
}


void table_print(table t) {
    printf(
        "| Key%*s| Value\n", STRING_KEY_CAP + 11 - 3, ""
    );

    for (uint64_t i = 0; i < t.count; ++i) {
        printf("| %*s%11d| %s\n", STRING_KEY_CAP, t.rows[i].key.key_s, t.rows[i].key.key_int, t.rows[i].value);
    }
}


void table_dealloc(table *t) {
    for (uint64_t i = 0; i < t->count; ++i) {
        t->rows[i].key.key_s[0] = '\0';
        t->rows[i].key.key_int = 0;
        free(t->rows[i].value);
    }

    free(t->rows);
}

#endif // TABLE_IMPLEMENTATION