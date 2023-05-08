#include <stdio.h>
#include <stdlib.h>

#include "tree.h"


void handle_add_delete(Node* n, int delete) {
    int command = 0;
    uint64_t node_index = 0;

    do {
        printf(
            "\n"
            "Do you want to go deeper into tree, stay, or go up? (1/0/-1)\n"
            "Current tree:\n"
        );
        node_print_tree(n);

        scanf("%d", &command);

        switch (command) {
            case -1:
                if (n->prev != NULL) {
                    n = n->prev;
                } else {
                    printf("Node has no parents!\n");
                }
                break;
            case 1:
                if (n->children[0] != NULL) {
                    uint64_t child_count = node_get_children_count(n);
                    node_index = 0;

                    if (child_count == 0) {
                        printf("Node has no children!\n");
                    } else {
                        if (child_count == 1) {
                            node_index = 0;
                        } else {
                            printf("Pick a node from 0 to %I64d in current node:\n", child_count - 1);
                            scanf("%I64d", &node_index);
                        }
                    }

                    if (node_index > child_count - 1) {
                        printf("No such child!\n");
                    } else {
                        n = n->children[node_index];
                    }
                } else {
                    printf("Node has no children!\n");
                }
                break;
            default:
                break;
        }
    } while (command != 0);


    if (delete) {
        if (n->prev == NULL) {
            printf("Current node is root! Can't delete it.\n");
            return;
        }

        node_delete_child(n->prev, node_index);
        return;
    }

    int64_t value = 0;
    printf("Input child value: ");
    scanf("%I64d", &value);

    Node** children = (Node**) calloc(2, sizeof(Node*));

    children[0] = (Node*) calloc(1, sizeof(Node));
    node_empty(children[0]);
    children[0]->value = value;

    children[1] = NULL;

    node_add_children(n, children, 1);
}

void print_menu() {
    printf(
        "Pick a command by typing a corresponding number\n\n"
        "1 - Add new node\n"
        "2 - Visualize tree\n"
        "3 - Delete a node\n"
        "4 - Check if tree's width is descending\n"
        "To exit press Ctrl + C\n\n"
    );
}


int main() {
    Node* root = (Node*) calloc(1, sizeof(Node));
    node_empty(root);

    while (1) {
        print_menu();

        int command = 0;
        scanf("%d", &command);

        printf("________________________\n");

        switch (command) {
        case 1:
            printf("Adding mode...\n");
            handle_add_delete(root, 0);
            printf("Current tree:\n");
            node_print_tree(root);
            break;
        case 2:
            printf("Tree visualizer...\n");
            node_print_tree(root);
            break;
        case 3:
            printf("Deleting mode...\n");
            handle_add_delete(root, 1);
            printf("Current tree:\n");
            node_print_tree(root);
            break;
        case 4:
            printf("Checking if tree's width is descending...\n");
            bool descends = node_is_width_descending(root);
            if (descends) {
                printf("The tree's width is descending!\n");
            } else {
                printf("The tree's width is not descending!\n");
            }
            break;
        default:
            printf("Unknown command...\n");
            break;
        }

        printf("\n");
    }

    return 0;
}
