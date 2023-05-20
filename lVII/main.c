#define SPARSE_MATRIX_IMPLEMENTATION
#include "smatrix.h"


int main() {
    FILE *f = fopen("m2.txt", "r");
    assert(f != NULL);

    // printf("?\n");
    SMatrix m = smatrix_from_file(f);

    smatrix_print(m);
    smatrix_print_debug(m);

    fclose(f);

    smatrix_free(&m);

    return 0;
}