#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tree.h"
#include "misc.h"


#define SEPARATOR "  "


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

    n->left->prev = &n;
    n->right->prev = &n;

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
            last_bracket_depth = bracket_depth;

            if (op == ' ') {
                op = n->tokens[length][0];
                lowest_priority_op_ind = length;
            } else if (op == '^') {
                op = n->tokens[length][0];
                lowest_priority_op_ind = length;
            } else if (op == '/' && n->tokens[length][0] == '*') {
                op = n->tokens[length][0];
                lowest_priority_op_ind = length;
            } else if ((op == '*' || op == '/') && (n->tokens[length][0] == '+' || n->tokens[length][0] == '-')) {
                op = n->tokens[length][0];
                lowest_priority_op_ind = length;
            }
            // printf("\n");
        }
    }
    n->left->op = op;
    // printf("OP: %c\n\n", n->left->op);

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

    // printf("braces: %llu, %llu\n", left_braces, right_braces);
    // printf("lengths: %llu, %llu\n\n", left_length, right_length);

    n->left->tokens = (char**) calloc(left_length + 1, sizeof(char*)); // one extra for NULL
    n->right->tokens = (char**) calloc(right_length + 1, sizeof(char*));

    n->left->tokens[left_length - 1] = NULL;
    n->right->tokens[right_length - 1] = NULL;


    unsigned long long n_ind = 0;

    unsigned long long left_start = left_braces;
    if (left_length == 1) {
        // printf("GET THIS FOCKING LEFT MATE\n");
        n_ind = left_start;
        if (char_is_number(n->tokens[n_ind][0])) {
            n->left->value = atoll(n->tokens[n_ind]);
            // printf("NUMBER! %llu\n", n->left->value);
        } else {
            n->left->constant = n->tokens[n_ind];
            // printf("CONST! %s\n", n->left->constant);
        }
    } else {
        // printf("COPY TO L:\n");
        for (i = 0; i < left_length; ++i) {
            n_ind = left_start + i;
            n->left->tokens[i] = (char*) calloc(strlen(n->tokens[n_ind]), sizeof(char));
            for (j = 0; j < strlen(n->tokens[n_ind]); ++j) {
                n->left->tokens[i][j] = n->tokens[n_ind][j];
            }
            // printf("%s", n->left->tokens[i]);
        }
        // printf("\n");
    }
    // printf("\n");

    unsigned long long right_start = left_length + 1 + 2 * left_braces + right_braces;
    if (right_length == 1) {
        // printf("GET THIS FOCKING RIGHT MATE\n");
        n_ind = right_start;
        if (char_is_number(n->tokens[n_ind][0])) {
            n->right->value = atoll(n->tokens[n_ind]);
            // printf("NUMBER! %llu\n", n->right->value);
        } else {
            n->right->constant = n->tokens[n_ind];
            // printf("CONST! %s\n", n->right->constant);
        }
    } else {
        // printf("COPY TO R:\n");
        for (i = 0; i < right_length; ++i) {
            n_ind = right_start + i;
            n->right->tokens[i] = (char*) calloc(strlen(n->tokens[n_ind]), sizeof(char));
            for (j = 0; j < strlen(n->tokens[n_ind]); ++j) {
                n->right->tokens[i][j] = n->tokens[n_ind][j];
            }
            // printf("%s", n->right->tokens[i]);
        }
        // printf("\n");
    }
    // printf("\n");
}

void node_build_tree(Node* n) {
    // printf("[NET]\n");
    if (n->tokens == NULL) return;

    unsigned long long length;
    for (length = 0; n->tokens[length] != NULL; ++length);
    if (length > 0) {
        // printf("===CHID===\n");
        node_create_children(n);
        // printf("===LEFT===\n");
        node_build_tree(n->left);
        // printf("===RIHT===\n");
        node_build_tree(n->right);
    // } else {
    //     printf("EMPTY!\n\n");
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

void node_print_tree(Node* n, int lvl) {
    if (n == NULL) return;

    lvl += 1;
    int seps = (int) (strlen(SEPARATOR) * lvl);

    node_print_tree(n->right, lvl);

    if (n->constant == NULL) {
        if (n->value != -1) {
            printf("%*s%lld", (int) (seps - strlen(SEPARATOR)), SEPARATOR, n->value);
        }
    } else {
        printf("%*s%s", (int) (seps - strlen(SEPARATOR)), SEPARATOR, n->constant);
    }

    if (n->left != NULL) printf("%*s%c", seps, SEPARATOR, n->left->op);
    printf("\n");

    node_print_tree(n->left, lvl);
}


void node_task(Node* n) {
    if (
        n->left == NULL || n->right == NULL ||
        n->left->left == NULL || n->left->right == NULL ||
        n->right->left == NULL || n->right->right == NULL
    ) return;

    Node* v = n->left;
    if (
        v->left->left == NULL && v->left->right == NULL &&
        v->right->left == NULL && v->right->right == NULL
    ) {
        node_take_out_factors(n);
    } else {
        node_task(n->left);
    }

    v = n->right;
    if (
        v->left->left == NULL && v->left->right == NULL &&
        v->right->left == NULL && v->right->right == NULL
    ) {
        node_take_out_factors(n);
    } else {
        node_task(n->right);
    }
}


void node_take_out_factors(Node* n) {    
    long long llv = n->left->left->value, lrv = n->left->right->value;
    long long rlv = n->right->left->value, rrv = n->right->right->value;

    char *ll = n->left->left->constant, *lr = n->left->right->constant;
    char *rl = n->right->left->constant, *rr = n->right->right->constant;

    if (
        (n->left->op != '-' || n->left->left->op != '*') ||
        (n->left->left->op != n->right->left->op) ||
        (
            ( // check if no matching numbers are present
                ((llv != -1 && rlv != -1) && llv != rlv) ||
                ((llv != -1 && rrv != -1) && llv != rrv) ||
                ((lrv != -1 && rlv != -1) && lrv != rlv) ||
                ((lrv != -1 && rrv != -1) && lrv != rrv)
            )
            ||
            ( // check if no matching constants are present
                ((ll != NULL && rl != NULL) && strcmp(ll, rl) != 0) ||
                ((ll != NULL && rr != NULL) && strcmp(ll, rr) != 0) ||
                ((lr != NULL && rl != NULL) && strcmp(lr, rl) != 0) ||
                ((lr != NULL && rr != NULL) && strcmp(lr, rr) != 0)
            )
        )
    ) return;

    n->right->left->op = n->left->op;
    n->left->op = n->left->left->op;

    long long value1 = -1, value2 = -1;

    if (llv != -1 && lrv != -1 && rlv != -1 && rrv != -1) {
        long long factor = -1;

        if (llv == rlv) {
            factor = llv;
            value1 = lrv;
            value2 = rrv;
        } else if (llv == rrv) {
            factor = llv;
            value1 = lrv;
            value2 = rlv;
        } else if (lrv == rlv) {
            factor = lrv;
            value1 = llv;
            value2 = rrv;
        } else {
            factor = lrv;
            value1 = llv;
            value2 = rlv;
        }

        n->left->value = factor;
    } else if ((ll != NULL || lr != NULL) && (rl != NULL || rr != NULL)) {
        char* constant;

        if (ll != NULL) {
            if (rl != NULL && strcmp(ll, rl) == 0) {
                constant = ll;
                n->right->left->constant = NULL;
                value1 = lrv;
                value2 = rrv;
            } else if (rr != NULL && strcmp(ll, rr) == 0) {
                constant = ll;
                n->right->right->constant = NULL;
                value1 = lrv;
                value2 = rlv;
            }
        } else if (lr != NULL) {
            if (rl != NULL && strcmp(lr, rl) == 0) {
                constant = lr;
                n->right->left->constant = NULL;
                value1 = llv;
                value2 = rrv;
            } else if (rr != NULL && strcmp(lr, rr) == 0) {
                constant = lr;
                n->right->right->constant = NULL;
                value1 = llv;
                value2 = rlv;
            }
        }

        n->left->constant = constant;
    }
    n->right->left->value = value1;
    n->right->right->value = value2;

    n->left->left = NULL;
    n->left->right = NULL;
}
