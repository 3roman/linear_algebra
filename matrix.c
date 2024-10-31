#include "matrix.h"

/*
The method of indexing any elements in matrix (i.e. two-dimension array) that stored in
one-dimension array is "row index * number of columns + column index".
*/

matrix* create_matrix(int rows, int cols) {
    matrix* output = (matrix*)malloc(sizeof(matrix));
    if (!output) return NULL;
    // calloc will directly return null matrix in lieu of subsequent memset when using malloc
    output->data = calloc(rows * cols, sizeof(double));
    if (!output->data) {
        free(output);
        return NULL;
    }
    output->rows = rows;
    output->cols = cols;

    return output;
}

int free_matrix(matrix* input) {
    if (input != NULL) {
        if (input->data != NULL) {
            free(input->data);
            input->data = NULL;
        }
        free(input);
        input = NULL;
    }

    return 0;
}

int print_matrix(matrix* input) {
    double* input_data = input->data;
    printf("%dx%d\n", input->rows, input->cols);
    for (int i = 0; i < input->rows; i++) {
        for (int j = 0; j < input->cols; j++) {
            printf("%-12.6f", *(input_data++));
        }
        printf("\n");
    }

    return 0;
}

matrix* scale_matrix(matrix* input, double scale) {
    matrix* output = create_matrix(input->rows, input->cols);
    for (int i = 0; i < input->rows * input->cols; i++) {
        output->data[i] = input->data[i] * scale;
    }

    return output;
}

matrix* transpose_matrix(matrix* input) {
    matrix* output = create_matrix(input->cols, input->rows);
    for (int i = 0; i < output->rows; i++) {
        for (int j = 0; j < output->cols; j++) {
            output->data[i * output->cols + j] = input->data[j * input->cols + i];
        }
    }

    return output;
}

matrix* dot_product_matrixes(matrix* a, matrix* b) {
    if (a->cols != b->rows) return NULL;
    matrix* c = create_matrix(a->rows, b->cols);

    for (int i = 0; i < c->rows; i++) {
        for (int j = 0; j < c->cols; j++) {
            for (int k = 0; k < a->cols; k++) {
                double a_element = a->data[i * a->cols + k];
                double b_element = b->data[k * b->cols + j];
                c->data[i * c->cols + j] += a_element * b_element;
            }
        }
    }

    return c;
}
