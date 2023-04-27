#include <stdio.h>
#include "tree.h"

int main() {
    Node root, other;

    // char initial_expression[256] = {};
    // printf("Input math expression: ");
    // scanf("%s", &initial_expression);

    // node_create_root(&root, "((1+(12)))- (bebra * 13)^(45/1)");
    node_create_root(&root, "3*9 - 3 * 5 + 50");
    // node_create_root(&root, "1+2+3+4");
    // node_create_root(&root, initial_expression);

    // printf("INIT:\n");
    // for (int i = 0; root.tokens[i] != NULL; ++i) {
    //     printf("%s", root.tokens[i]);
    // }
    // printf("\n\n");

    node_build_tree(&root);
    // node_print(root);
    node_print_tree(&root, 0);
    // printf("\n");

    node_take_out_factors(&root);
    node_print(root);
    printf("\n");

    return 0;
}