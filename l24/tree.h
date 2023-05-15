#ifndef TREE_H
#define TREE_H

#include <inttypes.h>

#ifdef DEBUG
#define DEBUG 0
#endif

typedef struct Node {
    char** tokens;
    char op;
    char* constant;
    int64_t value;
    struct Node* left;
    struct Node* right;
    struct Node* prev;
} Node;

void node_zero(Node* n);
void node_create_root(Node* n, char* lex);

void node_create_children(Node* n);
void node_build_tree(Node* n);

void node_print(Node n);
void node_print_tree(Node* n, int lvl);
void node_print_debug(Node n);

void node_task(Node* n);
void node_take_out_factors(Node* l, Node* r);


#endif