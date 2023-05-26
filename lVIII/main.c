#define LINKED_LIST_IMPLEMENTATION
#include "linked-list.h"

#include <assert.h>

int main() {
    linked_list *ll = ll_alloc();

    ll_set_value(ll, "aboba");
    ll_push_right(ll, "7");
    ll_push_right(ll, "2");
    ll_push_right(ll, "3");
    ll_push_right(ll, "4");
    ll_push_right(ll, "5");
    ll_print(ll);
    ll_dealloc(ll);

    return 0;
}