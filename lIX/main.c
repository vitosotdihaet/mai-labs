#define TABLE_IMPLEMENTATION
#include "table.h"


int main() {
    table t = table_alloc();

    uint64_t count = 0;
    printf("Input how many rows do you want to insert: ");
    scanf("%llu", &count);

    for (uint64_t i = 0; i < count; ++i) {
        printf("Row %llu:\n", i);

        char *key_s = (char*) calloc(256, sizeof(char));
        printf("Input key string: ");
        scanf("%s", key_s);

        int key_int = 0;
        printf("Input key int: ");
        scanf("%d", &key_int);

        char *value = (char*) calloc(256, sizeof(char));
        printf("Input value string: ");
        scanf("%s", value);

        table_push(&t, key_s, key_int, value);

        free(key_s);

        printf("\n");
    }

    table_print(t);
    printf("\n");
    t = table_quick_sort(t);
    table_print(t);

    int search = 1;
    while (search) {
        char *key_s = (char*) calloc(256, sizeof(char));
        int key_int = 0;
        printf("Search for:\n");
        scanf("%s", key_s);
        scanf("%d", &key_int);

        printf("Found string: %s\n", table_binary_search(t, key_s, key_int));
        free(key_s);

        printf("Do you want to continue the search? (0/1): ");
        scanf("%d", &search);
    }

    table_dealloc(&t);
}