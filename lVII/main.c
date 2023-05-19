#define SPARSE_MATRIX_IMPLEMENTATION
#include "smatrix.h"


int main() {
    SMatrix m = smatrix_alloc(3, 4);

    smatrix_print(m);

    return 0;
}