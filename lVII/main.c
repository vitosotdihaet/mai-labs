#define SPARSE_MATRIX_IMPLEMENTATION
#include "smatrix.h"


int main() {
    FILE *f = fopen("m3.txt", "r");
    assert(f != NULL);

    SMatrix m = smatrix_from_file(f);

    printf("Initial matrix:\n");
    printf("(Real matrix)\n");
    smatrix_print(m);
    printf("(Internal structure)\n");
    smatrix_print_debug(m);

    printf(
        "========================================\n"
        "Transposed by secondary diagonal matrix:\n"
    );
    SMatrix t = smatrix_transpose_sec_diag(m);
    printf("(Real matrix)\n");
    smatrix_print(t);
    printf("(Internal structure)\n");
    smatrix_print_debug(t);

    printf("\n");
    if (smatrix_is_skew_symmetric(t)) {
        printf("The matrix is skew-symmetric!\n");
    } else {
        printf("The matrix is not skew-symmetric...\n");
    }

    smatrix_free(&m);
    smatrix_free(&t);
    fclose(f);

    return 0;
}