#define LINKED_LIST_IMPLEMENTATION
#include "linked-list.h"

#include <signal.h>


void handle_add(linked_list *ll) {
    uint64_t i = 0;
    printf("Input index, where you want to add your value in: ");
    scanf("%d", &i);

    char *value = (char*) calloc(256, sizeof(char));
    printf("Input value you want to add at %llu is ", i);
    scanf("%s", value);

    ll_add_ith(ll, i, value);

    free(value);
}

linked_list* handle_remove(linked_list *ll) {
    uint64_t i = 0;
    printf("Input index of element that you want to remove: ");
    scanf("%d", &i);

    return ll_remove_ith(ll, i);
}

void handle_check_sort(linked_list *ll) {
    if (ll_is_sorted(ll)) {
        printf("Linked list is sorted!\n");
    } else {
        printf("Linked list is not sorted!\n");
    }
}


linked_list* handle_command(int c, linked_list *ll) {
    printf("\n");

    switch (c) {
        case 1:
            handle_add(ll);
            break;
        case 2:
            ll = handle_remove(ll);
            break;
        case 3:
            handle_check_sort(ll);
            break;
        default:
            printf("Invalid command!\n");
    }

    return ll;
}


void print_menu() {
    printf(
        "===========================================\n"
        "Input number of command you want to execute\n"
        "1 - Add element\n"
        "2 - Remove element\n"
        "3 - Check if list is sorted\n"
        "To exit - press Ctrl + C\n\n"
    );
}

static volatile linked_list *ll;

void handle_sigint(int _) {
    ll_dealloc(ll);
    exit(0);
}


int main() {
    ll = ll_alloc();
    int c = 0;

    signal(SIGINT, handle_sigint);

    while (1) {
        print_menu();
        printf("Current list: ");
        ll_print(ll);

        printf("\nYour command: ");
        scanf("%d", &c);

        ll = handle_command(c, ll);
    }

    ll_dealloc(ll);

    return 0;
}