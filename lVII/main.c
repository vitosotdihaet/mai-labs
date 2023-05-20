#define SPARSE_MATRIX_IMPLEMENTATION
#include "smatrix.h"


int main() {
    FILE *f = fopen("m2.txt", "r");
    assert(f != NULL);

    smatrix_print(smatrix_from_file(f));

    // SMatrix m = smatrix_alloc(3, 4);

    // smatrix_set(&m, 0, 0, 11.f);
    // smatrix_set(&m, 0, 1, 12.f);
    // smatrix_set(&m, 1, 0, 21.f);
    // smatrix_set(&m, 0, 3, 14.f);

    // SMATRIX_PRINT_NAMED(m);

    return 0;
}