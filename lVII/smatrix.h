#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// =================================
// Structure:
// rows_s = {0, 2, 3}
// cols_i = {
//     0, 1,               (1 2 0)
//     1,                =>(0 3 0) ?
//     2                   (0 0 4)
// }
// values = {1, 2, 3, 4}

typedef struct SMatrix {
    uint64_t rows;
    uint64_t cols;
    float* values;
    uint64_t* rows_s;
    uint64_t* cols_i;
} SMatrix;


SMatrix smatrix_alloc(uint64_t rows, uint64_t cols);
float smatrix_at(SMatrix m, uint64_t i, uint64_t j);
void smatrix_print(SMatrix m);
void smatrix_set(SMatrix m, uint64_t i, uint64_t j, float v);


#endif // SPARSE_MATRIX_H



#ifdef SPARSE_MATRIX_IMPLEMENTATION
#define SPARSE_MATRIX_IMPLEMENTATION


SMatrix smatrix_alloc(uint64_t rows, uint64_t cols) {
    SMatrix m;
    m.rows = rows;
    m.cols = cols;
    m.values = (float*) malloc(rows * cols * sizeof(*m.values));

    assert(m.values != NULL);

    m.rows_s = (uint64_t*) malloc(0 * sizeof(*m.rows_s));
    m.cols_i = (uint64_t*) malloc(0 * sizeof(*m.cols_i));

    return m;
}

float smatrix_at(SMatrix m, uint64_t i, uint64_t j) {
    for (uint64_t ind = 0; m.rows_s[ind + 1]; ++ind) {
        if (i <= m.rows_s[ind]) {
            for (uint64_t c = 0; c < m.cols; ++c) {
                if (c == j) return m.values[c];
            }
        }
    }
    return 0;
}

void smatrix_print(SMatrix m) {
    for (uint64_t i = 0; i < m.rows; ++i) {
        for (uint64_t j = 0; j < m.cols; ++j) {
            printf("%f ", smatrix_at(m, i, j));
        }
        printf("\n");
    }
}

void smatrix_set(SMatrix m, uint64_t i, uint64_t j, float v) {
    assert(i < m.rows);
    assert(j < m.cols);

    
}


#endif // SPARSE_MATRIX_IMPLEMENTATION