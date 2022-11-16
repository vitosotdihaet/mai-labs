#ifndef STRING_H

#define STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


typedef struct string {
    char *values;
    uint64_t last_element;
    uint64_t memory_size;
} string;


// Initialize string with default capacity
int init_string(string* s);

// Adds memory
int string_resize(string* s, uint64_t capacity);

// Copies s2 to s1 (taking minimal memory size) -> s1='aboba', s2='bobr' -> s1='bobr '
int copy_string(string* s1, string s2);

// Adds a char to string, adding more memory if needed 
int add_char(string* s, char value);

// Reads string char by char returning 1 if EOF
int read_string(string* s);

int reverse_string(string* s);

#endif