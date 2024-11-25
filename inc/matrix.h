#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct _matrix {
    int height;
    int width;
    double* data;
} matrix;

matrix* create_matrix(int height, int width);
int free_matrix(matrix* input);
int print_matrix(const matrix* input, int decimal_places);
matrix* scale_matrix(const matrix* m, double scale);
matrix* transpose_matrix(const matrix* m);
matrix* inverse_matrix(const matrix* input);
matrix* add_matrixes(const matrix* a, const matrix* b);
matrix* dot_product_matrixes(const matrix* a, const matrix* b);

#endif
