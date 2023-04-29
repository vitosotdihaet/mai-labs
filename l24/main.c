#include <stdio.h>
#include "tree.h"

int main() {
    Node root, other;

    // char initial_expression[256] = {};
    // printf("Input math expression: ");
    // scanf("%s", &initial_expression);

    // node_create_root(&root, "((1+(12)))- (bebra * 13)^(45/1)+among");
    // node_create_root(&root, "((1+2))-((7) + 13)");
    node_create_root(&root, "3*9 - 3 * 5 + 50");
    // node_create_root(&root, "1+2+3+4");
    // node_create_root(&root, initial_expression);

    // printf("INIT:\n");
    // for (int i = 0; root.tokens[i] != NULL; ++i) {
    //     printf("%s", root.tokens[i]);
    // }
    // printf("\n\n");

    printf("Original:\n");
    node_build_tree(&root);
    node_print(root);
    printf("\n");
    node_print_tree(&root, 0);
    printf("\n");

    printf("Task:\n");
    // node_task(&root);

    node_print(*root.left);
    printf("\n");
    node_print(*root.right->left);
    printf("\n");

    // printf("\n");

    // node_take_out_factors(root.left, root.right->left);
    node_print_debug(*root.left);
    printf("\n");
    // node_print_debug(*root.right->left);
    // printf("\n");

    // printf("\n");
    // node_print(root);
    printf("\n");

    return 0;
}