#include <stdio.h>
#include "tree.h"

int main() {
    Node root;

    node_create_root(&root, "1+2");
    node_add_children(&root);
    node_add_children(&root.left);
    node_print(root);

    return 0;
}