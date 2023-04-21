#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tree.h"
#include "misc.h"


void node_zero(Node* n) {
    n->tokens = NULL;
    n->op = ' ';
    n->constant = NULL;
    n->value = -1;
    n->left = NULL;
    n->right = NULL;
    n->prev = NULL;
}

void node_create_root(Node* n, char* lex) {
    node_zero(n);
    char** tokens = (char**) calloc(strlen(lex), sizeof(char*));

    char lop = ' ';
    unsigned long long i, j, t = 0;

    for (i = 0; lex[i] != '\0'; ++i) {
        j = 0;
        if (lex[i] == ' ') continue;

        if (char_is_operation(lex[i])) {
            tokens[t] = (char*) calloc(1, sizeof(char));
            tokens[t][0] = lex[i];
            j = 1;
        } else {
            tokens[t] = (char*) calloc(10, sizeof(char));

            if ('0'<= lex[i] && lex[i] <= '9') {
                for (j = 0; lex[i + j] != '\0' && char_is_number(lex[i + j]); ++j);
            } else {
                for (j = 0; lex[i + j] != '\0' && !char_is_operation(lex[i + j]) && lex[i + j] != ' '; ++j);
            }

            memcpy(tokens[t], lex + i, j);
        }

        i += j - 1;
        ++t;
    }

    n->tokens = tokens;
}


void node_create_children(Node* n) {
    n->left = (Node *) calloc(1, sizeof(Node));
    n->right = (Node *) calloc(1, sizeof(Node));
    node_zero(n->left);
    node_zero(n->right);

    unsigned long long length, i, j;

    for (length = 0; n->tokens[length] != NULL; ++length);
    n->left->tokens = (char**) calloc(length - 1, sizeof(char*)); // one extra for NULL

    if (char_is_number(n->tokens[length - 1][0])) {
        n->right->value = atoll(n->tokens[length - 1]);
    } else {
        n->right->constant = n->tokens[length - 1];
    }

    n->left->op = n->tokens[length - 2][0]; 
    // TODO: move to right node tokens whole expression and handle them; example: 2^(3 + 5)
    // TODO: handle priorities of operations
    if (length == 3) {
        if (char_is_number(n->tokens[0][0])) {
            n->left->value = atoll(n->tokens[0]);
        } else {
            n->left->constant = n->tokens[0];
        }
    } else {
        for (i = 0; i < length - 2; ++i) {
            n->left->tokens[i] = (char*) calloc(strlen(n->tokens[i]), sizeof(char));
            for (j = 0; j < strlen(n->tokens[i]); ++j) {
                n->left->tokens[i][j] = n->tokens[i][j];
            }
        }
    }
    n->left->tokens[length - 2] = NULL;
}

void node_add_children(Node* n) {
    if (n->tokens == NULL) {
        return;
    }
    node_create_children(n);
}

void node_empty_tokens(Node* n) {
    // printf("[NET]\n");
    unsigned long long length;
    for (length = 0; n->tokens[length] != NULL; ++length);
    // printf("\n");
    // printf("len: %llu\n", length);
    if (length > 0) {
        node_add_children(n);
        // printf("children have ben added succesfully\n");
        // printf("%lld and %lld\n", n->left->value, n->right->value);
        // printf("\n");
        node_empty_tokens(n->left);
    }
}


void node_print(Node n) {
    if (n.left != NULL) {
        printf("(");
        node_print(*n.left);
        printf("%c", n.left->op);
    }

    if (n.constant == NULL) {
        if (n.value != -1) {
            printf("%lld", n.value);
        }
    } else {
        printf("%s", n.constant);
    }

    if (n.right != NULL) {
        node_print(*n.right);
        printf(")");
    }
}
