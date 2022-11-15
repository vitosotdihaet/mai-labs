#include "string.h"

//? Maybe deprecated, but those are for error handling
#define UNDEFINED 0
#define SUCCESS 1
#define ERROR -1

// How big initial memory is
const uint64_t INIT_CAPACITY = 2;
// How big relative to previous allocated memory new memory should be
const uint64_t EXTENDED_CAPACITY = 2;

// Memory-related macros 
#define new(a, n) (a*)calloc(n, sizeof(a) * n)
#define reallocate(ptr, a, n) (a*)realloc(ptr, sizeof(a) * n)

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

// Initialize string with default capacity
int init_string(string* s) {
    int result = UNDEFINED;
    s->memory_size = INIT_CAPACITY;
    s->values = new(char, INIT_CAPACITY);
    s->last_element = 0;
    return result;
}

// Sets all struct's parameters to zero
int free_string(string* s) {
    s->memory_size = INIT_CAPACITY;
    s->values = new(char, 0);
    s->last_element = 0;
    return SUCCESS;
}

// Adds memory
int string_resize(string* s, uint64_t capacity) {
    uint64_t new_capacity = s->memory_size * capacity;
    s->memory_size = new_capacity;
    s->values = reallocate(s->values, char, new_capacity);
    return SUCCESS;
}

// Adds a char to string, adding more memory if needed 
int add_char(string* s, char value) {
    int result = UNDEFINED;
    if (s->last_element < s->memory_size) {
        result = SUCCESS;
    } else {
        result = string_resize(s, EXTENDED_CAPACITY);
    }
    s->values[s->last_element] = value;
    s->last_element++;
    return result;
}

// Reads string char by char returning 1 if EOF
int read_string(string* s) {
    char c = ' ';
    int end = 0;

    while (1) {
        c = getchar();
        if (c == ' ' || c == ',' || c == '\t' || c == '\n') {
            break;
        } else if ((int) c == EOF) {
            end = 1;
            break;
        }
        add_char(s, c);
    }

    return end;
}
