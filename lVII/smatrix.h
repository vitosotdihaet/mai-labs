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
void smatrix_free(SMatrix *m);


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

    m.cols_i = (uint64_t*) calloc(1, sizeof(*m.cols_i));
    m.values = (float*) calloc(1, sizeof(*m.values));

    m.elements = 0;

    return m;
}

SMatrix smatrix_from_file(FILE *f) {
    char *row_buf = (char*) calloc(256, sizeof(char));
    fgets(row_buf, 256, f);

    uint64_t rows = 0, cols = 0;

    for (uint64_t i = 0; i < strlen(row_buf); ++i) { // pre-count column count
        if (char_is_in_float(row_buf[i]) &&
            (row_buf[i + 1] == ' ' || row_buf[i + 1] == '\n')
        ) { // check how many times space or \n is present after float chars
            cols++;
        }
    }

    float **numbers = (float**) calloc(256, sizeof(float*)); // calloc for zeroing

    do {
        uint64_t len = strlen(row_buf), c = 0;
        if (row_buf[len - 1] == '\n') row_buf[len - 1] = '\0';

        for (uint64_t i = 0; i < len; ++i) { // parse current line
            while (row_buf[i] == ' ') ++i; // skip spaces before current number
            if (row_buf[i] == '\n') break;

            char *num_buf = (char*) calloc(256, sizeof(char)); // current number buffer

            for (uint64_t j = 0; j < len - i; ++j) { // parse current number
                char cur_c = row_buf[i + j];

                if (char_is_in_float(cur_c)) {
                    num_buf[j] = cur_c;
                } else {
                    i += j; // skip whole number for i
                    break;
                }
            }

            if (strlen(num_buf) == 0) {
                free(num_buf);
                break;
            }

            if (c == 0) { // alloc every time there is a new row
                numbers[rows] = (float*) calloc(cols, sizeof(float));
            }

            // printf("%f at r=%lu, c=%lu\n", strtof(num_buf, NULL), rows, c);
            numbers[rows][c] = strtof(num_buf, NULL);

            c++;
            free(num_buf);
        }

        rows++;
    } while (fgets(row_buf, 256, f) != NULL);

    free(row_buf);

    // printf("dims: %lu, %lu\n", rows, cols);

    SMatrix m = smatrix_alloc(rows, cols);

    for (uint64_t i = 0; i < rows; ++i) {
        for (uint64_t j = 0; j < cols; ++j) {
            float n = numbers[i][j];
            if (n != 0.f) {
                // printf("set %f at %lu %lu\n", numbers[i][j], i, j);
                smatrix_set(&m, i, j, n);
            }
        }
    }

    for (uint64_t i = 0; i < 256; ++i) {
        free(numbers[i]);
    }
    free(numbers);

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
    printf("rows = %lu, cols = %lu, elements = %lu\n", m.rows, m.cols, m.elements);

    printf("rows_s: [");
    for (uint64_t i = 0; i < m.rows; ++i)
        printf("%lu ", m.rows_s[i]);
    printf("(%lu) ", m.rows_s[m.rows]);
    printf("\b]\n");

    if (m.elements == 0)
        return;

    printf("cols_i: [");
    for (uint64_t i = 0; i < m.elements; ++i)
        printf("%lu ", m.cols_i[i]);
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
            // printf("m->elements = %lu\n", m->elements);
            // printf("realloc cols_i...\n");
            m->cols_i = (uint64_t*) realloc(m->cols_i, m->elements * sizeof(*m->cols_i));
            // printf("realloc values...\n");
            m->values = (float*) realloc(m->values, m->elements * sizeof(*m->values));

            // printf("lb...\n");
            uint64_t lb = m->rows_s[i];
            // printf("rb...\n");
            uint64_t rb = m->elements - 1;

            // printf("lb = %lu, rb = %lu\n", lb, rb);

            for (uint64_t move = rb; move > lb; --move) { // move right column indecies and values to right
                m->cols_i[move] = m->cols_i[move - 1]; // move - 1 to safely get to 0
                m->values[move] = m->values[move - 1];
            }

            m->cols_i[lb] = j;
            m->values[lb] = v;
        }
    }
}

void smatrix_free(SMatrix *m) {
    m->cols = 0;
    m->rows = 0;
    m->elements = 0;

    free(m->rows_s);
    free(m->cols_i);
    free(m->values);

    m = NULL;
}


#endif // SPARSE_MATRIX_IMPLEMENTATION