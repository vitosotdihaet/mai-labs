#include <stdio.h>
#include "tree.h"

#define DEBUG 1

int main() {
    Node root, other;

    // char initial_expression[256] = {};
    // printf("Input math expression: ");
    // scanf("%s", &initial_expression);

    // node_create_root(&root, "((1+(12)))- (bebra * 13)^(45/1)+among");
    // node_create_root(&root, "((1+2))-((7) + 13)");
    // node_create_root(&root, "1+2+3+4");
    // node_create_root(&root, initial_expression);

    node_create_root(&root, "3*9 - 3 * 5 + 50");
    printf("Original:\n");
    node_build_tree(&root);
    node_print(root);
    printf("\n");

    printf("Task:\n");
    // node_task(&root);
    node_take_out_factors(root.left, root.right->left);
    node_print(root);
    printf("\n");

    // printf("\n");

    // node_create_root(&root, "3*9 - 3 * 5");
    // printf("Original:\n");
    // node_build_tree(&root);
    // node_print(root);
    // printf("\n");

    // printf("Task:\n");
    // // node_task(&root);
    // node_take_out_factors(root.left, root.right);
    // node_print(root);
    // printf("\n");

    return 0;
}