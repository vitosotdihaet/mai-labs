#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct linked_list {
    struct linked_list *prev;
    struct linked_list *next;
    char *value;
} linked_list;


linked_list* ll_alloc();

void ll_set_value(linked_list *ll, const char *value);
void ll_push_right(linked_list *ll, const char *value);

linked_list* ll_leftmost(linked_list *ll);
linked_list* ll_rightmost(linked_list *ll);

linked_list* ll_remove(linked_list *ll);
linked_list* ll_remove_right(linked_list *ll);
linked_list* ll_remove_left(linked_list *ll);

void ll_print(linked_list *ll);
void ll_print_debug(linked_list *ll);

size_t ll_is_sorted(linked_list *ll);

void ll_dealloc(linked_list *ll);

#endif // LINKED_LIST_H



#ifdef LINKED_LIST_IMPLEMENTATION

linked_list* ll_alloc() {
    linked_list *ll = (linked_list*) calloc(1, sizeof(linked_list));

    ll->prev = NULL;
    ll->next = NULL;
    ll->value = (char*) calloc(1, sizeof(char)); // barrier element = "\0";

    return ll;
}


void ll_set_value(linked_list *ll, const char *value) {
    if (strcmp(ll->value, "") == 0) {
        linked_list *pl, *nl;

        if (ll->prev == NULL) {
            pl = ll_alloc();
            pl->next = ll;
            pl->prev = ll->prev;
            ll->prev = pl;
        }

        if (ll->next == NULL) {
            nl = ll_alloc();
            nl->next = ll->next;
            nl->prev = ll;
            ll->next = nl;
        }
    }

    free(ll->value);

    char* s = (char*) calloc(strlen(value) + 1, sizeof(char));
    strcpy(s, value);

    ll->value = s;
}

void ll_push_right(linked_list *ll, const char *value) {
    ll_set_value(ll_rightmost(ll), value);
}


linked_list* ll_leftmost(linked_list *ll) {
    while (strcmp(ll->value, "") != 0) {
        ll = ll->prev;
    }

    return ll;
}

linked_list* ll_rightmost(linked_list *ll) {
    while (strcmp(ll->value, "") != 0) {
        ll = ll->next;
    }

    return ll;
}


linked_list* ll_remove(linked_list *ll) {
    linked_list *next = ll->next;
    linked_list *prev = ll->prev;

    free(ll->value);
    free(ll);

    ll = prev;

    ll->next = next;
    ll->next->prev = prev;

    return prev;
}

linked_list* ll_remove_right(linked_list *ll) {
    ll = ll_rightmost(ll);
    return ll_remove(ll->prev)->prev;
}

linked_list* ll_remove_left(linked_list *ll) {
    ll = ll_leftmost(ll);
    return ll_remove(ll->next)->next;
}


void ll_print(linked_list *ll) {
    if (strcmp(ll->value, "") == 0) {
        printf("\n");
        return;
    }

    ll = ll_leftmost(ll);
    ll = ll->next;

    while (strcmp(ll->value, "") != 0) {
        printf("%s, ", ll->value);
        ll = ll->next;
    }

    printf("\b\b \b\n");
}

void ll_print_debug(linked_list *ll) {
    printf("ll: *%d, prev: *%d, next: *%d, value: %s\n", ll, ll->prev, ll->next, ll->value);
}


size_t ll_is_sorted(linked_list *ll) {
    ll = ll_leftmost(ll);

    while (strcmp(ll->next->value, "") != 0 && strcmp(ll->value, ll->next->value) <= 0) {
        ll = ll->next;
    }

    if (strcmp(ll->next->value, "") == 0) {
        return 1;
    } else {
        return 0;
    }
}


void ll_dealloc(linked_list *ll) {
    ll = ll_leftmost(ll);

    // do this outside of while loop, because ll.value = "\0"
    free(ll->value);
    ll = ll->next;

    while (strcmp(ll->value, "") != 0) {
        // printf("freeing value = %s\n", ll->value);
        // ll_print(ll);
        free(ll->value);
        free(ll->prev);

        ll = ll->next;
    }

    free(ll->prev);
    free(ll->value);
    free(ll);
}

#endif // LINKED_LIST_IMPLEMENTATION