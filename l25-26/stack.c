#ifndef STACK_H
#define STACK_H

#include "stack.h"

#include <stdlib.h>
#include <stdio.h>


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


int64_t stack_pop(stack* s) {
    if (s->_size == 0) {
        printf("Stack size is zero! Bailing...\n");
        exit(1);
    }
    s->_size--;
    return s->_arr[s->_size];
}

void stack_delete_at(stack* s, uint64_t index) {
    for (uint64_t i = index; i < s->_size; ++i) {
        s->_arr[i] = s->_arr[i + 1];
    }
    s->_size--;
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
    for (uint64_t i = 0; i < s->_size - 1; i++) {
        uint64_t min_index = i;

        for (uint64_t j = i + 1; j < s->_size; j++) {
            if (s->_arr[j] < s->_arr[min_index])
                min_index = j;
        }

        if (min_index != i) {
            int64_t temp = s->_arr[i];
            s->_arr[i] = s->_arr[min_index];
            s->_arr[min_index] = temp;
        }
    }
}

void stack_delete_max(stack* s) {
    uint64_t max_index = 0;
    int64_t max_element = INT64_MIN;
    for (uint64_t i = 0; i < s->_size; ++i) {
        if (s->_arr[i] > max_element) max_index = i;
    }
    stack_delete_at(s, max_index);
}

#endif