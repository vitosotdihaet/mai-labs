#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"

#define SEPARATOR " "
#define TABS "\t\t\t\t\t\t\t\t\t\t"


uint64_t max(uint64_t n1, uint64_t n2) {
    if (n1 > n2) return n1;
    return n2;
}

void node_empty(Node* n) {
    n->children = (Node**) calloc(1, sizeof(Node*));
    n->children[0] = NULL;
    n->prev = NULL;
    n->value = 0;
}

void node_set_children(Node* n, Node** children, uint64_t count) {
    n->children = (Node**) calloc(count + 1, sizeof(Node*));
    for (uint64_t i = 0; i < count; ++i) {
        n->children[i] = children[i];
        n->children[i]->prev = n;
        n->children[i]->value = children[i]->value;
    }
    n->children[count] = NULL;
}

uint64_t node_get_children_count(Node* n) {
    uint64_t count = 0;
    while (n->children[count] != NULL) ++count;
    return count;
}


void _node_print_tree(Node* n, int lvl) {
    if (n == NULL) return;

    lvl += 1;
    int seps = (int) (strlen(SEPARATOR) * lvl);

    printf("%*s%I64d", (int) (seps - strlen(SEPARATOR)), SEPARATOR, n->value);
    printf("\n");

    if (n->children[0] == NULL) return;

    printf("%*s\\\n", (int) (seps - strlen(SEPARATOR) + 1), SEPARATOR);
    for (uint64_t i = 0; n->children[i] != NULL; ++i) {
        _node_print_tree(n->children[i], lvl);
    }
}

void node_print_tree(Node* n) {
    _node_print_tree(n, 1);
}


bool node_is_width_descending(Node* n) {
    if (n == NULL) return true;
    uint64_t node_count = node_get_children_count(n), count = 0;
    for (uint64_t i = 0; n->children[i] != NULL; ++i) {
        count = max(count, node_get_children_count(n->children[i]));
    }

    if (count > node_count) {
        return false;
    } else {
        bool is_descending = true;
        for (uint64_t i = 0; n->children[i] != NULL || !is_descending; ++i) {
            is_descending = is_descending && node_is_width_descending(n->children[i]);
        }
        return is_descending;
    }
}