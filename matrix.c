#include "matrix.h"

/*
The method of indexing any elements in matrix (i.e. two-dimension array) that stored in one-dimension array is "row index * number of columns + column index".
*/

matrix* create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        fprintf(stderr, "invalid matrix dimensions.\n");
        return NULL;
    }

    matrix* output = (matrix*)malloc(sizeof(matrix));
    if (!output) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }
    // calloc will directly return null matrix in lieu of subsequent memset when using malloc
    output->data = calloc(rows * cols, sizeof(double));
    if (!output->data) {
        free(output);
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }
    output->rows = rows;
    output->cols = cols;

    return output;
}

int free_matrix(matrix* input) {
    if (input) {
        free(input->data);
        free(input);
        input = NULL;
    }

    return 0;
}

int print_matrix(const matrix* input, int decimal_places) {
    if (!input) {
        fprintf(stderr, "null reference.\n");
        return -1;
    }
    double* input_data = input->data;
    if (!input_data) {
        fprintf(stderr, "null reference.\n");
        return -1;
    }
    printf("%dx%d\n", input->rows, input->cols);

    char format[20];
    snprintf(format, sizeof(format), "%%-%d.%df", decimal_places * 2, decimal_places);

    for (int i = 0; i < input->rows; i++) {
        for (int j = 0; j < input->cols; j++) {
            printf(format, *(input_data++));
        }
        printf("\n");
    }

    return 0;
}

matrix* scale_matrix(const matrix* input, double scale) {
    if (!input) {
        fprintf(stderr, "null reference.\n");
        return NULL;
    }
    matrix* output = create_matrix(input->rows, input->cols);
    if (!output) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }

    for (int i = 0; i < input->rows * input->cols; i++) {
        output->data[i] = input->data[i] * scale;
    }

    return output;
}

matrix* transpose_matrix(const matrix* input) {
    if (!input) {
        fprintf(stderr, "null reference.\n");
        return NULL;
    }
    matrix* output = create_matrix(input->cols, input->rows);
    if (!output) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }

    for (int i = 0; i < output->rows; i++) {
        for (int j = 0; j < output->cols; j++) {
            output->data[i * output->cols + j] = input->data[j * input->cols + i];
        }
    }

    return output;
}

matrix* add_matrixes(const matrix* a, const matrix* b) {
    if (!a || !b) {
        fprintf(stderr, "null reference.\n");
        return NULL;
    }
    if (a->cols != b->cols || a->rows != b->rows) {
        fprintf(stderr, "inconsistent dimensions.\n");
        return NULL;
    }
    matrix* c = create_matrix(a->rows, b->cols);
    if (!c) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            c->data[i * a->cols + j] = a->data[i * a->cols + j] + b->data[i * a->cols + j];
        }
    }

    return c;
}

matrix* dot_product_matrixes(const matrix* a, const matrix* b) {
    if (!a || !b) {
        fprintf(stderr, "null reference.\n");
        return NULL;
    }
    if (a->cols != b->rows) {
        fprintf(stderr, "A's columns must equal B's rows.\n");
        return NULL;
    };
    matrix* c = create_matrix(a->rows, b->cols);
    if (!c) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }

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

matrix* inverse_matrix(const matrix* input) {
    if (!input) {
        fprintf(stderr, "null reference.\n");
        return NULL;
    }
    if (input->rows != input->cols) {
        fprintf(stderr, "matrix must be square.\n");
        return NULL;
    }

    int n = input->rows;
    matrix* augmented = create_matrix(n, 2 * n);
    if (!augmented) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }

    // Initialize the augmented matrix [A | I]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented->data[i * (2 * n) + j] = input->data[i * n + j];
            augmented->data[i * (2 * n) + (j + n)] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Perform Gauss-Jordan elimination
    for (int i = 0; i < n; i++) {
        // Make the diagonal contain all 1s
        double diag = augmented->data[i * (2 * n) + i];
        if (diag == 0) {
            free_matrix(augmented);
            fprintf(stderr, "Matrix is singular and cannot be inverted.\n");
            return NULL;
        }
        for (int j = 0; j < 2 * n; j++) {
            augmented->data[i * (2 * n) + j] /= diag;
        }

        // Make the other rows contain 0s in the current column
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = augmented->data[k * (2 * n) + i];
                for (int j = 0; j < 2 * n; j++) {
                    augmented->data[k * (2 * n) + j] -= factor * augmented->data[i * (2 * n) + j];
                }
            }
        }
    }

    // Extract the inverse matrix
    matrix* output = create_matrix(n, n);
    if (!output) {
        free_matrix(augmented);
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            output->data[i * n + j] = augmented->data[i * (2 * n) + (j + n)];
        }
    }

    free_matrix(augmented);
    return output;
}
