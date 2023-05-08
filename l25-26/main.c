#include <stdio.h>
#include "stack.h"

int main() {
    stack* s = stack_empty();

    int64_t arr[9] = {5, 13, 7, 4, 8, 1, -152, 7, 12};

    for (int i = 0; i < 5; ++i) {
        stack_push(s, i);
    }

    // printf("Top 3 after adding 0 1 2 3 4:\n");
    // for (int i = 0; i < 3; ++i) {
    //     printf("%I64d\n", stack_pop(s));
    // }

    stack_push_array(s, 9, arr);

    printf("Initial stack:\n");
    stack_print(s);

    // stack_delete_max(s);
    // printf("Stack after deleting max element from it:\n");

    stack_sort(s);
    printf("Stack after sorting:\n");

    stack_print(s);

    return 0;
}
