#include <stdio.h>

#define TREE_DEBUG 0
#define TREE_IMPLEMENTATION

#include "tree.h"


int main() {
    Node root;

    node_create_root(&root, "3*9 - 3 * 5 + 50");
    printf("Original:\n");
    node_build_tree(&root);
    node_print(root);
    printf("\nTree form:\n");
    node_print_tree(&root);
    printf("\n");

    printf("Task:\n");
    node_take_out_factors(root.left->left, root.left->right);
    node_print(root);
    printf("\nTree form:\n");
    node_print_tree(&root);
    printf("\n");

    printf("\n");

    node_create_root(&root, "3*9 + 50 - 3 * 5");
    printf("Original:\n");
    node_build_tree(&root);
    printf("\nTree form:\n");
    node_print_tree(&root);
    node_print(root);
    printf("\n");

    printf("Task:\n");
    node_take_out_factors(root.left, root.right->right);
    node_print(root);
    printf("\nTree form:\n");
    node_print_tree(&root);
    printf("\n");
    
    printf("\n");

    node_create_root(&root, "y*x - z * x + 50");
    printf("Original:\n");
    node_build_tree(&root);
    node_print(root);
    printf("\nTree form:\n");
    node_print_tree(&root);
    printf("\n");

    printf("Task:\n");
    node_take_out_factors(root.left->left, root.left->right);
    node_print(root);
    printf("\nTree form:\n");
    node_print_tree(&root);
    printf("\n");


    char expr[256] = {};
    printf("\nInput your math expression (without spaces): ");
    scanf("%s", &expr);

    node_create_root(&root, expr);
    printf("Original:\n");
    node_build_tree(&root);
    node_print(root);
    printf("\nTree form:\n");
    node_print_tree(&root);
    printf("\n");

    printf("Task:\n");
    node_take_out_factors(root.left, root.right);
    node_print(root);
    printf("\nTree form:\n");
    node_print_tree(&root);
    printf("\n");

    return 0;
}