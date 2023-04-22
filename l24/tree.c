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
    char** tokens = (char**) calloc(strlen(lex) + 1, sizeof(char*));
    tokens[strlen(lex)] = NULL;

    unsigned long long i, j, t = 0;

    for (i = 0; lex[i] != '\0'; ++i) {
        j = 0;
        if (lex[i] == ' ') continue;

        if (char_is_operation(lex[i]) || char_is_bracket(lex[i])) {
            tokens[t] = (char*) calloc(1, sizeof(char));
            tokens[t][0] = lex[i];
            j = 1;
        } else {
            tokens[t] = (char*) calloc(10, sizeof(char));

            if ('0'<= lex[i] && lex[i] <= '9') {
                for (j = 0; lex[i + j] != '\0' && char_is_number(lex[i + j]); ++j);
            } else {
                for (j = 0; lex[i + j] != '\0' && !char_is_operation(lex[i + j]) &&
                            lex[i + j] != ' ' && !char_is_bracket(lex[i + j]); ++j);
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

    unsigned long long length = 0, i = 0, j = 0;
    unsigned long long lowest_priority_op_ind = 0, bracket_depth = 0, last_bracket_depth = 0;
    char op = ' ';

    for (length = 0; n->tokens[length] != NULL; ++length) {
        // printf("LEN = %llu\n", length);
        if (n->tokens[length][0] == '(') {
            bracket_depth++;
            // printf("+BD: %llu\n", bracket_depth);
            continue;
        } else if (n->tokens[length][0] == ')') {
            bracket_depth--;
            // printf("-BD: %llu\n", bracket_depth);
            continue;
        }

        if (bracket_depth > last_bracket_depth) continue;

        if (char_is_operation(n->tokens[length][0])) {
            // printf("found op: %c; type: ", n->tokens[length][0]);
            last_bracket_depth = bracket_depth;

            if (op == ' ') {
                // printf("1");
                op = n->tokens[length][0];
                lowest_priority_op_ind = length;
            } else if (op == '^') {
                // printf("2");
                op = n->tokens[length][0];
                lowest_priority_op_ind = length;
            } else if ((op == '*' || op == '/') && (n->tokens[length][0] == '+' || n->tokens[length][0] == '-')) {
                // printf("3");
                op = n->tokens[length][0];
                lowest_priority_op_ind = length;
            }
            printf("\n");
        }
    }
    n->left->op = op;
    printf("OP: %c\n\n", n->left->op);

    unsigned long long left_length = lowest_priority_op_ind;
    unsigned long long right_length = length - left_length - 1;

    unsigned long long left_braces = 0, right_braces = 0;
    for (i = 0; i < left_length/2; ++i) {
        if (n->tokens[i][0] == '(' && n->tokens[length - right_length - 2 - i][0] == ')') {
            left_length -= 2;
            left_braces++;
        }
    }

    for (i = 0; i < right_length; ++i) {
        if (n->tokens[left_length + 1 + 2 * left_braces + i][0] == '(' && n->tokens[length - 1 - i][0] == ')') {
            right_length -= 2;
            right_braces++;
        } else break;
    }

    printf("braces: %llu, %llu\n", left_braces, right_braces);
    printf("lengths: %llu, %llu\n\n", left_length, right_length);

    n->left->tokens = (char**) calloc(left_length + 1, sizeof(char*)); // one extra for NULL
    n->right->tokens = (char**) calloc(right_length + 1, sizeof(char*));

    n->left->tokens[left_length - 1] = NULL;
    n->right->tokens[right_length - 1] = NULL;


    unsigned long long n_ind = 0;

    if (left_length == 1) {
        printf("GET THIS FOCKING LEFT MATE\n");
        n_ind = left_braces;
        if (char_is_number(n->tokens[n_ind][0])) {
            n->left->value = atoll(n->tokens[n_ind]);
            printf("NUMBER! %llu\n", n->left->value);
        } else {
            n->left->constant = n->tokens[n_ind];
            printf("CONST! %s\n", n->left->constant);
        }
    } else {
        printf("COPY TO L:\n");
        for (i = 0; i < left_length; ++i) {
            n_ind = i + left_braces;
            n->left->tokens[i] = (char*) calloc(strlen(n->tokens[n_ind]), sizeof(char));
            for (j = 0; j < strlen(n->tokens[n_ind]); ++j) {
                n->left->tokens[i][j] = n->tokens[n_ind][j];
            }
            printf("%s", n->left->tokens[i]);
        }
        printf("\n");
    }
    printf("\n");

    if (right_length == 1) {
        printf("GET THIS FOCKING RIGHT MATE\n");
        n_ind = left_length + 1 + 2 * left_braces + right_braces;
        if (char_is_number(n->tokens[n_ind][0])) {
            n->right->value = atoll(n->tokens[n_ind]);
            printf("NUMBER! %llu\n", n->right->value);
        } else {
            n->right->constant = n->tokens[n_ind];
            printf("CONST! %s\n", n->right->constant);
        }
    } else {
        printf("COPY TO R:\n");
        for (i = 0; i < right_length; ++i) {
            n_ind = left_length + 1 + 2 * left_braces + right_braces + i;
            n->right->tokens[i] = (char*) calloc(strlen(n->tokens[n_ind]), sizeof(char));
            for (j = 0; j < strlen(n->tokens[n_ind]); ++j) {
                n->right->tokens[i][j] = n->tokens[n_ind][j];
            }
            printf("%s", n->right->tokens[i]);
        }
        printf("\n");
    }
    printf("\n");
}

void node_build_tree(Node* n) {
    // printf("[NET]\n");
    if (n->tokens == NULL) return;

    unsigned long long length;
    for (length = 0; n->tokens[length] != NULL; ++length);
    if (length > 0) {
        printf("===CHID===\n");
        node_create_children(n);
        printf("===LEFT===\n");
        node_build_tree(n->left);
        printf("===RIHT===\n");
        node_build_tree(n->right);
    } else {
        printf("EMPTY!\n\n");
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
