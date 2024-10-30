#include "matrix.h"

int assert(int assertion, char* message) {
    if (assertion == 0) {
        fprintf(stderr, "%s\n", message);
        exit(1);
    }

    return 0;
}

matrix* create_matrix(int rows, int cols) {
    assert(cols > 0 && rows > 0, "New matrix must be at least a 1 by 1");
    matrix* out = (matrix*)malloc(sizeof(matrix));
    assert(out != NULL, "Out of memory.");

    out->rows = rows;
    out->cols = cols;
    out->data = (double*)calloc(rows * cols, sizeof(double));
    assert(out->data != NULL, "Out of memory.");

    return out;
}

int free_matrix(matrix* m) {
    if (m != NULL) {
        if (m->data != NULL) {
            free(m->data);
            m->data = NULL;
        }
        free(m);
        m = NULL;
    }

    return 0;
}

int print_matrix(matrix* m) {
    double* ptr = m->data;
    printf("%dx%d\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%-12.6f", *(ptr++));
        }
        printf("\n");
    }

    return 0;
}

matrix* transpose_matrix(matrix* m) {
    matrix* out = create_matrix(m->cols, m->rows);
    double* ptr_out;
    double* ptr_m = m->data;

    for (int i = 0; i < m->rows; i++) {
        ptr_out = &out->data[i];
        for (int j = 0; j < m->cols; j++) {
            *ptr_out = *ptr_m;
            ptr_m++;
            ptr_out += out->cols;
        }
    }

    return out;
}

matrix* dot_product_matrixes(matrix* a, matrix* b) {
    double* ptr_a;
    double* ptr_b;
    assert(a->rows == b->cols, "Matrices have incorrect dimensions. a->width != b->height");

    matrix* out = create_matrix(a->rows, b->cols);
    double* ptrOut = out->data;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            ptr_a = &a->data[i * a->rows];
            ptr_b = &b->data[j];

            *ptrOut = 0;
            for (int k = 0; k < a->rows; k++) {
                *ptrOut += *ptr_a * *ptr_b;
                ptr_a++;
                ptr_b += b->rows;
            }
            ptrOut++;
        }
    }

    return out;
}

matrix* scale_matrix(matrix* m, double scale) {
    matrix* out = create_matrix(m->rows, m->cols);
    for (int i = 0; i < out->rows * out->cols; i++) {
        out->data[i] = m->data[i] * scale;
    }

    return out;
}
