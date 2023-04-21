#include <stdio.h>
#include "tree.h"

int main() {
    Node root;

    // node_create_root(&root, "1+12- bebra * 13^45/1");
    node_create_root(&root, "1+12");
    for (int i = 0; root.tokens[i] != NULL; ++i) {
        printf("%s", root.tokens[i]);
    }
    printf("\n");
    // node_create_children(&root);
    // printf("%lld\n", root.right->value);
    node_empty_tokens(&root);
    node_print(root);
    printf("\n");

    return 0;
}