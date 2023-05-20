#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

// =================================
// Structure:
// rows_s = {0, 2, 3}, len(rows_s) <= rows
// cols_i = {
//     0, 1,               (1 2 0)
//     1,                =>(0 3 0)
//     2                   (0 0 4)
// }
// values = {1, 2, 3, 4}

typedef struct SMatrix {
    uint64_t rows;
    uint64_t cols;
    uint64_t elements;
    float* values;
    uint64_t* rows_s;
    uint64_t* cols_i;
} SMatrix;

#define SMATRIX_PRINT_NAMED(m) printf("%s = ", #m); smatrix_print(m)


SMatrix smatrix_alloc(uint64_t rows, uint64_t cols);
SMatrix smatrix_from_file(FILE *f);
float smatrix_at(SMatrix m, uint64_t i, uint64_t j);
void smatrix_print(SMatrix m);
void smatrix_print_debug(SMatrix m);
void smatrix_set(SMatrix *m, uint64_t i, uint64_t j, float v);


#endif // SPARSE_MATRIX_H



#ifdef SPARSE_MATRIX_IMPLEMENTATION
#define SPARSE_MATRIX_IMPLEMENTATION

int char_is_in_float(char cur_c) {
    return ('0' <= cur_c && cur_c <= '9') || cur_c == '.' || cur_c == '-';
}


SMatrix smatrix_alloc(uint64_t rows, uint64_t cols) {
    SMatrix m;
    m.rows = rows;
    m.cols = cols;
    m.rows_s = (uint64_t*) calloc(rows + 1, sizeof(*m.rows_s));
    assert(m.rows_s != NULL);

    m.cols_i = (uint64_t*) calloc(0, sizeof(*m.cols_i));
    m.values = (float*) calloc(0, sizeof(*m.values));

    m.elements = 0;

    return m;
}

SMatrix smatrix_from_file(FILE *f) {
    char row_buf[256];
    uint64_t rows = 0, cols = 0;

    fgets(row_buf, 256, f);
    for (uint64_t i = 0; i < strlen(row_buf); ++i) { // pre-count column count
        if (char_is_in_float(row_buf[i]) && (row_buf[i + 1] == ' ' || row_buf[i + 1] == '\n')) {
            cols++;
        }
    }

    float **numbers = (float**) calloc(256, sizeof(float*)); // calloc for zeroing

    do {
        uint64_t len = strlen(row_buf), c = 0;
        if (row_buf[len - 1] == '\n') row_buf[len - 1] = '\0';

        for (uint64_t i = 0; i < len; ++i) { // parse current line
            char *num_buf = (char*) calloc(256, sizeof(char));
            float number = 0.f;

            while (row_buf[i] == ' ') ++i; // skip spaces before current number

            for (uint64_t j = 0; j < len - i; ++j) { // parse current number
                char cur_c = row_buf[i + j];

                if (char_is_in_float(cur_c)) {
                    num_buf[j] = cur_c;
                } else {
                    i += j; // skip whole number for i
                    break;
                }
            }

            number = strtof(num_buf, NULL);

            if (c == 0) { // alloc every time there is a new row
                numbers[rows] = (float*) calloc(cols, sizeof(float));
            }

            numbers[rows][c] = number;

            c++;
        }
        rows++;
    } while (fgets(row_buf, 256, f) != NULL);

    SMatrix m = smatrix_alloc(rows, cols);

    for (uint64_t i = 0; i < rows; ++i) {
        for (uint64_t j = 0; j < cols; ++j) {
            if (numbers[i][j] != 0.f) {
                printf("%I64d, %I64d:\n", i, j);
                smatrix_set(&m, i, j, numbers[i][j]);
                smatrix_print_debug(m);
            }
        }
    }

    return m;
}

float smatrix_at(SMatrix m, uint64_t i, uint64_t j) {
    assert(i < m.rows);
    assert(j < m.cols);

    for (uint64_t c = m.rows_s[i]; c < m.rows_s[i + 1]; ++c) {
        if (m.cols_i[c] == j) return m.values[c];
    }

    return 0;
}

void smatrix_print(SMatrix m) {
    printf("[\n");
    for (uint64_t i = 0; i < m.rows; ++i) {
        for (uint64_t j = 0; j < m.cols; ++j) {
            printf("%8.3f ", smatrix_at(m, i, j));
        }
        printf("\n");
    }
    printf("]\n");
}

void smatrix_print_debug(SMatrix m) {
    printf("rows = %I64d, cols = %I64d, elements = %I64d\n", m.rows, m.cols, m.elements);

    printf("rows_s: [");
    for (uint64_t i = 0; i < m.rows; ++i)
        printf("%I64d ", m.rows_s[i]);
    printf("(%I64d) ", m.rows_s[m.rows]);
    printf("\b]\n");

    if (m.elements == 0)
        return;

    printf("cols_i: [");
    for (uint64_t i = 0; i < m.elements; ++i)
        printf("%I64d ", m.cols_i[i]);
    printf("\b]\n");

    printf("values: [");
    for (uint64_t i = 0; i < m.elements; ++i)
        printf("%f ", m.values[i]);
    printf("\b]\n");
}

void smatrix_set(SMatrix *m, uint64_t i, uint64_t j, float v) {
    assert(i < m->rows);
    assert(j < m->cols);

    for (uint64_t ind = 0; ind < m->rows + 1; ++ind) {
        if (i < ind) {
            // {.., 3, 3, ..} -> {.., 3, 4, ..}
            m->rows_s[ind]++;
        } else if (i == ind) {
            m->elements++;
            m->cols_i = (uint64_t*) realloc(m->cols_i, m->elements);

            uint64_t lb = m->rows_s[i];
            uint64_t rb = m->elements - 1;

            printf("\n");
            printf("pre-moved:\n");
            printf("value = %f\n", m->values[0]);
            smatrix_print_debug(*m);

            printf("l = %I64d, r = %I64d\n", lb, rb);
            for (uint64_t move = rb; move > lb; --move) { // move right column indecies and values to right
                m->cols_i[move] = m->cols_i[move - 1]; // move-1 to safely get to 0
                m->values[move] = m->values[move - 1];
            }

            printf("value = %f\n", m->values[0]);
            printf("m.rows_s[%I64d] = %I64d\n", i, m->rows_s[i]);

            m->cols_i[m->rows_s[i]] = j;
            m->values[m->rows_s[i]] = v;

            printf("post-post:\n");
            printf("value = %f\n", m->values[0]);
            smatrix_print_debug(*m);
            printf("\n");
        }
    }
}


#endif // SPARSE_MATRIX_IMPLEMENTATION