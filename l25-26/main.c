#include <stdio.h>
#include "stack.h"

int main() {
    stack* s = stack_empty();

    int64_t arr[9] = {5, 13, 7, 4, 8, 1, -152, 7, 12};

    for (int i = 0; i < 5; ++i) {
        stack_push(s, i);
    }

    for (int i = 0; i < 9; ++i) {
        stack_push(s, arr[i]);
    }
    printf("Stack before popping:\n");
    stack_print(s);

    for (int i = 0; i < 3; ++i) {
        stack_pop(s);
    }
    printf("Stack after popping:\n");
    stack_print(s);

    stack_delete_max(s);
    printf("Stack after deleting max element from it:\n");
    stack_print(s);

    stack_sort(s);
    printf("Stack after sorting:\n");
    stack_print(s);

    stack_delete_max(s);
    printf("Stack after deleting max element from it:\n");
    stack_print(s);

    for (int i = 0; i < 3; ++i) {
        stack_pop(s);
    }
    printf("Stack after popping 3 elements from it:\n");
    stack_print(s);

    for (int i = 10; i < 15; ++i) {
        stack_push(s, -i + 40);
    }
    printf("Stack after pushing to it:\n");
    stack_print(s);

    stack_delete_max(s);
    printf("Stack after deleting max element from it:\n");
    stack_print(s);

    stack_sort(s);
    printf("Stack after sorting:\n");
    stack_print(s);

    return 0;
}
