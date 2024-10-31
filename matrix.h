#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _matrix {
    int rows;
    int cols;
    double* data;
} matrix;

matrix* create_matrix(int rows, int cols);
int free_matrix(matrix* m);
int print_matrix(matrix* m);
matrix* scale_matrix(matrix* m, double scale);
matrix* transpose_matrix(matrix* m);
matrix* dot_product_matrixes(matrix* a, matrix* b);

#endif
