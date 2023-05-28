#define LINKED_LIST_IMPLEMENTATION
#include "linked-list.h"

#include <assert.h>

int main() {
    linked_list *ll = ll_alloc();

    ll_set_value(ll, "aaa");
    
    ll_push_right(ll, "b");
    ll_push_right(ll, "c");
    ll_push_right(ll, "eerh");
    ll_push_right(ll, "d");
    ll_push_right(ll, "faa");
    printf("Initial list:\n");
    ll_print(ll);
    
    ll = ll_remove(ll->next);
    printf("Without second element:\n");
    ll_print(ll);

    ll = ll_remove_left(ll);
    printf("Without leftmost element:\n");
    ll_print(ll);

    if (ll_is_sorted(ll)) {
        printf("Linked list is sorted!\n");
    } else {
        printf("Linked list is not sorted!\n");
    }

    ll = ll_remove_right(ll);
    printf("Without rightmost element:\n");
    ll_print(ll);

    if (ll_is_sorted(ll)) {
        printf("Linked list is sorted!\n");
    } else {
        printf("Linked list is not sorted!\n");
    }

    ll_dealloc(ll);

    return 0;
}