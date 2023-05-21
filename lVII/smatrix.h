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

SMatrix smatrix_transpose(SMatrix m);
SMatrix smatrix_transpose_sec_diag(SMatrix m);

float smatrix_at(SMatrix m, uint64_t i, uint64_t j);

void smatrix_print(SMatrix m);
void smatrix_print_debug(SMatrix m);

void smatrix_set(SMatrix *m, uint64_t i, uint64_t j, float v);
void smatrix_mult(SMatrix m, float n);
int smatrix_eq(SMatrix m1, SMatrix m2);

int smatrix_is_skew_symmetric(SMatrix m);

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
    char row_buf[256] = {};
    fgets(row_buf, 256, f);

    uint64_t rows = 0, cols = 0;

    for (uint64_t i = 0; i < strlen(row_buf); ++i) { // pre-count column count
        if (char_is_in_float(row_buf[i]) &&
            (row_buf[i + 1] == ' ')
        ) { // check how many times space or \n is present after float chars
            cols++;
        }
    }
    cols++;

    // printf("cols = %llu\n", cols);

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

            // printf("%f at r=%llu, c=%llu\n", strtof(num_buf, NULL), rows, c);
            numbers[rows][c] = strtof(num_buf, NULL);

            c++;
            free(num_buf);
        }

        rows++;
    } while (fgets(row_buf, 256, f) != NULL);

    // printf("dims: %llu, %llu\n", rows, cols);

    SMatrix m = smatrix_alloc(rows, cols);

    for (uint64_t i = 0; i < rows; ++i) {
        for (uint64_t j = 0; j < cols; ++j) {
            float n = numbers[i][j];
            if (n != 0.f) {
                // printf("set %f at %llu %llu\n", numbers[i][j], i, j);
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


SMatrix smatrix_transpose(SMatrix m) {
    SMatrix t = smatrix_alloc(m.cols, m.rows);

    for (uint64_t i = 0; i < m.rows; ++i) {
        for (uint64_t j = 0; j < m.cols; ++j) {
            float n = smatrix_at(m, i, j);
            if (n != 0.f) {
                smatrix_set(&t, j, i, n);
            }
        }
    }

    return t;
}

SMatrix smatrix_transpose_sec_diag(SMatrix m) {
    SMatrix t = smatrix_alloc(m.cols, m.rows);

    for (uint64_t i = 0; i < m.rows; ++i) {
        for (uint64_t j = 0; j < m.cols; ++j) {
            float n = smatrix_at(m, i, j);
            if (n != 0.f) {
                smatrix_set(&t, m.cols - j - 1, m.rows - i - 1, n);
            }
        }
    }

    return t;
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
    printf("rows = %llu, cols = %llu, elements = %llu\n", m.rows, m.cols, m.elements);

    printf("rows_s: [");
    for (uint64_t i = 0; i < m.rows; ++i)
        printf("%llu ", m.rows_s[i]);
    printf("(%llu) ", m.rows_s[m.rows]);
    printf("\b]\n");

    if (m.elements == 0)
        return;

    printf("cols_i: [");
    for (uint64_t i = 0; i < m.elements; ++i)
        printf("%llu ", m.cols_i[i]);
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
            // printf("m->elements = %llu\n", m->elements);
            // printf("realloc cols_i...\n");
            m->cols_i = (uint64_t*) realloc(m->cols_i, m->elements * sizeof(*m->cols_i));
            // printf("realloc values...\n");
            m->values = (float*) realloc(m->values, m->elements * sizeof(*m->values));

            // printf("lb...\n");
            uint64_t lb = m->rows_s[i];
            // printf("rb...\n");
            uint64_t rb = m->elements - 1;

            // printf("lb = %llu, rb = %llu\n", lb, rb);

            for (uint64_t move = rb; move > lb; --move) { // move right column indecies and values to right
                m->cols_i[move] = m->cols_i[move - 1]; // move - 1 to safely get to 0
                m->values[move] = m->values[move - 1];
            }

            m->cols_i[lb] = j;
            m->values[lb] = v;
        }
    }
}

void smatrix_mult(SMatrix m, float n) {
    if (n == 0.f) {
        m = smatrix_alloc(m.rows, m.cols);
        return;
    }

    for (uint64_t i = 0; i < m.elements; ++i) {
        m.values[i] *= n;
    }
}

int smatrix_eq(SMatrix m1, SMatrix m2) {
    if (m1.cols != m2.cols || m1.rows != m2.rows) {
        return 0;
    }

    for (uint64_t i = 0; i < m1.rows; ++i) {
        for (uint64_t j = 0; j < m1.cols; ++j) {
            if (smatrix_at(m1, i, j) != smatrix_at(m2, i, j)) {
                return 0;
            }
        }
    }

    return 1;
}


int smatrix_is_skew_symmetric(SMatrix m) {
    SMatrix t = smatrix_transpose(m);
    smatrix_mult(m, -1.f);

    if (smatrix_eq(m, t)) {
        smatrix_mult(m, -1.f);
        return 1;
    }

    smatrix_mult(m, -1.f);
    return 0;
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