#ifndef TREE_H
#define TREE_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct Node {
    struct Node* prev;
    struct Node** children;
    int64_t value;
} Node;


void node_empty(Node* n);
void node_set_children(Node* n, Node** children, uint64_t count);
uint64_t node_get_children_count(Node* n);

void node_print_tree(Node* n);

bool node_is_width_descending(Node* n);


#endif