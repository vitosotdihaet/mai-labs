#include <stdio.h>
#include "stack.h"

int main() {
    stack* s = stack_empty();
    int64_t arr[3] = {1, -5, 342}; 

    for (int i = 0; i < 5; ++i) {
        stack_push(s, i);
    }

    printf("Top 3 after adding 0 1 2 3 4:\n");
    for (int i = 0; i < 3; ++i) {
        printf("%I64d\n", stack_pop(s));
    }

    stack_push_array(s, 3, arr);
    printf("Top 4 after adding array {1, -5, 342} and deleting max element from it:\n");
    // stack_sort(s);
    stack_delete_max(s);
    for (int i = 0; i < 4; ++i) {
        printf("%I64d\n", stack_pop(s));
    }

    return 0;
}
