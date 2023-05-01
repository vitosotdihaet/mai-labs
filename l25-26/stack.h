#include <inttypes.h>
#include <stdbool.h>

typedef struct stack {
    uint64_t _size;
    uint64_t _capacity;
    int64_t *_arr;
} stack;


stack* stack_empty();
stack* stack_from_array(uint64_t size, int64_t* elements);

uint64_t stack_size(stack* s);
uint64_t stack_capacity(stack* s);
bool stack_is_empty(stack* s);

int64_t stack_pop(stack* s);
void stack_delete_at(stack* s, uint64_t index);

void stack_push(stack* s, int64_t e);
void stack_push_array(stack* s, uint64_t size, int64_t* elements);

void stack_free (stack *s);


void stack_sort(stack* s);
void stack_delete_max(stack* s);