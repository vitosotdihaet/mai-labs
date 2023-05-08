#ifndef STACK_H
#define STACK_H

#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


stack* stack_empty() {
    stack* s;
    s = (stack*) calloc(1, sizeof(stack));
    s->_arr = calloc(1, sizeof(int64_t));
    s->_size = 0;
    s->_capacity = 1;
    return s;
}

stack* stack_from_array(uint64_t size, int64_t* elements) {
    stack* s = stack_empty();
    stack_push_array(s, size, elements);
    return s;
}


uint64_t stack_size(stack* s) {
    return s->_size;
}

uint64_t stack_capacity(stack* s) {
    return s->_capacity;
}

bool stack_is_empty(stack* s) {
    return s->_size == 0;
}

void stack_print(stack* s) {
    uint64_t length = s->_size;
    stack* temp = stack_empty();

    for (uint64_t i = 0; i < length; ++i) {
        int64_t top = stack_pop(s);
        stack_push(temp, top);
        printf("%I64d\n", top);
    }

    for (uint64_t i = 0; i < length; ++i) {
        stack_push(s, stack_pop(temp));
    }
}


int64_t stack_pop(stack* s) {
    if (s->_size == 0) {
        printf("Stack size is zero! Bailing...\n");
        exit(1);
    }
    s->_size--;
    return s->_arr[s->_size];
}

void stack_delete_at(stack* s, uint64_t index) {
    assert(index < s->_size);

    stack* temp = stack_empty();
    for (uint64_t i = 0; i < index; ++i) {
        stack_push(temp, stack_pop(s));
    }

    stack_pop(s);

    for (uint64_t i = index; i > 0; --i) {
        stack_push(s, stack_pop(temp));
    }
}


void _stack_resize(stack* s, uint64_t new_capacity) {
    s->_capacity = new_capacity;
    s->_arr = (int64_t*) realloc(s->_arr, new_capacity * sizeof(int64_t));
}

void stack_push(stack* s, int64_t e) {
    if (s->_size + 1 > s->_capacity) {
        _stack_resize(s, 2 * s->_capacity);
    }
    s->_arr[s->_size] = e;
    s->_size++;
    s->_arr[s->_size] = 0;
}

void stack_push_array(stack* s, uint64_t size, int64_t* elements) {
    for (uint64_t i = 0; i < size; ++i) {
        stack_push(s, elements[i]);
    }
}


void stack_free(stack* s) {
    s->_size = 0;
    s->_capacity = 0;
    free(s->_arr);
}



void stack_sort(stack* s) {
    stack* sorted = stack_empty();

    stack* temp = stack_empty();
    stack* temp1 = stack_empty();

    while (!stack_is_empty(s)) {
        uint64_t length = s->_size;

        uint64_t min_index = 0;
        int64_t min_element = stack_pop(s);
        stack_push(temp, min_element);

        for (uint64_t j = 1; j < length; ++j) {
            int64_t min_element1 = stack_pop(s);
            stack_push(temp1, min_element1);
            if (min_element1 < min_element) {
                min_index = j;
                min_element = min_element1;
            }
        }

        if (min_index != 0) {
            for (uint64_t j = min_index + 1; j < length; ++j)
                stack_push(s, stack_pop(temp1));

            stack_push(sorted, stack_pop(temp1));

            for (uint64_t j = 1; j < min_index; ++j)
                stack_push(s, stack_pop(temp1));

            stack_push(s, stack_pop(temp));
        } else {
            stack_push(sorted, stack_pop(temp));
            for (uint64_t j = 1; j < length; ++j) {
                stack_push(s, stack_pop(temp1));
            }
        }
    }
    *s = *sorted;
}

void stack_delete_max(stack* s) {
    stack* temp = stack_empty();

    uint64_t max_index = 0;
    int64_t max_element = INT64_MIN;

    uint64_t length = s->_size;

    for (uint64_t i = 0; i < length; ++i) {
        int64_t top = stack_pop(s);
        if (top > max_element) {
            max_element = top;
            max_index = i;
        }
        stack_push(temp, top);
    }

    for (uint64_t i = 0; i < length; ++i) {
        stack_push(s, stack_pop(temp));
    }

    stack_delete_at(s, max_index);
}


#endif