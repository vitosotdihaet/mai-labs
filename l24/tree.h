#ifndef TREE_H
#define TREE_H

struct Node {
    char** tokens;
    char op;
    char* constant;
    long long value;
    struct Node* left;
    struct Node* right;
    struct Node* prev;
};
typedef struct Node Node;

void node_zero(Node* n);
void node_create_root(Node* n, char* lex);

void node_create_children(Node* n);
void node_build_tree(Node* n);

void node_print(Node n);
void node_print_tree(Node* n, int lvl);

void node_task(Node* l, Node* r);
void node_take_out_factors(Node* n);


#endif