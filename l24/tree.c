#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


void node_zero(Node* n) {
    n->lex = (char*) calloc(1, sizeof(char));
    n->op = ' ';
    n->constant = ' ';
    n->value = -1;
    n->left = NULL;
    n->right = NULL;
    n->prev = NULL;
}

void node_create_root(Node* n, char* lex) {
    node_zero(n);
    n->lex = lex;
}

void node_create_children_from_lex(Node* left, Node* right, char* lex) {
    unsigned long long length = 0;
    printf("[LEX]: %s\n", lex);

    char lop = ' ';
    unsigned long long i, last_i = 0;

    for (i = 0; lex[i] != '\0'; ++i) {
        length = i + 1;
        char cop = lex[i];
        printf("[COP]: %c\n", cop);
        if (cop == '+' || cop == '-' || cop == '*' || cop == '/' || cop == '^') {
            last_i = i;
            lop = cop;
        }

        if (lex[i + 1] == '\0') {
            if ('0' <= cop && cop <= '9') {
                char* value_buf = (char*) calloc(10, sizeof(char));
                memcpy(value_buf, lex + last_i + 1, length - last_i - 1);
                right->value = atoll(value_buf);
                printf("[INFO]: atolling: %lld\n", right->value);
            } else {
                printf("[INFO]: const!\n");
                right->constant = cop;
            }
        }
    }

    memcpy(left->lex, lex, last_i);
    printf("[LEX LEFT]: %s\n", left->lex);
    left->op = lop;
    printf("[LOP]: %c\n", left->op);
}

void node_add_children(Node* n) {
    if (sizeof(n->lex) == 0) {
        return;
    }
    Node l, r;
    node_zero(&l);
    node_zero(&r);
    node_create_children_from_lex(&l, &r, n->lex);
    n->left = &l;
    n->right = &r;
}

void node_print(Node n) {
    printf("[PRINTING...]\n");
    if (n.left != NULL) {
        printf("left:\n");
        printf("(");
        node_print(*n.left);
        printf("\nend of left\n");
    }

    if (n.constant == ' ') {
        if (n.value != -1) {
            printf("%lld", n.value);
        }
    } else {
        printf("%c", n.constant);
    }

    if (n.op != ' ') {
        printf("%c", n.op);
    }

    if (n.right != NULL) {
        printf("right:\n");
        node_print(*n.right);
        printf(")");
        printf("\nend of right\n");
    }
    printf("\n");
}