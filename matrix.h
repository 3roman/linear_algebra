#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct _matrix {
    int rows;
    int cols;
    double* data;
} matrix;

matrix* create_matrix(const int rows, const int cols);
int free_matrix(matrix* input);
int print_matrix(const matrix* input, const int decimal_places);
matrix* scale_matrix(const matrix* m, const double scale);
matrix* transpose_matrix(const matrix* m);
matrix* inverse_matrix(const matrix* input);
matrix* add_matrixes(const matrix* a, const matrix* b);
matrix* dot_product_matrixes(const matrix* a, const matrix* b);

#endif
