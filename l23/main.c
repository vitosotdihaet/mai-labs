#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main() {
    Node* n = (Node*) calloc(1, sizeof(Node));
    Node** children = calloc(5 + 1, sizeof(Node*));

    for (uint64_t i = 0; i < 5; ++i) {
        Node* c = (Node*) calloc(1, sizeof(Node));
        node_empty(c);
        c->value = i;
        children[i] = c;
    }
    children[5] = NULL;

    node_empty(n);
    n->value = 500;

    node_set_children(n, children, 5);
    node_print_tree(n);

    if (node_is_width_descending(n))
        printf("tree's width is descending\n");
    else
        printf("tree's width is not descending\n");


    Node** children1 = calloc(7 + 1, sizeof(Node*));

    for (uint64_t i = 0; i < 7; ++i) {
        Node* c = (Node*) calloc(1, sizeof(Node));
        node_empty(c);
        c->value = i;
        children1[i] = c;
    }

    children1[7] = NULL;

    node_set_children(n->children[1], children1, 7);
    node_print_tree(n);

    if (node_is_width_descending(n))
        printf("tree's width is descending\n");
    else
        printf("tree's width is not descending\n");


    return 0;
}