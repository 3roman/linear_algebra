#include "../inc/matrix.h"

/*
The method of indexing any elements in matrix (i.e. two-dimension array) that stored in one-dimension array is "row index * number of columns + column index".
*/

matrix* create_matrix(int height, int width) {
    if (height <= 0 || width <= 0) {
        fprintf(stderr, "invalid matrix dimensions.\n");
        return NULL;
    }

    matrix* output = (matrix*)malloc(sizeof(matrix));
    if (!output) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }
    // calloc will directly return null matrix in lieu of subsequent memset when using malloc
    output->data = calloc(height * width, sizeof(double));
    if (!output->data) {
        free(output);
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }
    output->height = height;
    output->width = width;

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
    printf("%dx%d\n", input->height, input->width);

    char format[20];
    snprintf(format, sizeof(format), "%%-%d.%df", decimal_places * 2, decimal_places);

    for (int i = 0; i < input->height; i++) {
        for (int j = 0; j < input->width; j++) {
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
    matrix* output = create_matrix(input->height, input->width);
    if (!output) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }

    for (int i = 0; i < input->height * input->width; i++) {
        output->data[i] = input->data[i] * scale;
    }

    return output;
}

matrix* transpose_matrix(const matrix* input) {
    if (!input) {
        fprintf(stderr, "null reference.\n");
        return NULL;
    }
    matrix* output = create_matrix(input->width, input->height);
    if (!output) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }

    for (int i = 0; i < output->height; i++) {
        for (int j = 0; j < output->width; j++) {
            output->data[i * output->width + j] = input->data[j * input->width + i];
        }
    }

    return output;
}

matrix* add_matrixes(const matrix* a, const matrix* b) {
    if (!a || !b) {
        fprintf(stderr, "null reference.\n");
        return NULL;
    }
    if (a->width != b->width || a->height != b->height) {
        fprintf(stderr, "inconsistent dimensions.\n");
        return NULL;
    }
    matrix* c = create_matrix(a->height, b->width);
    if (!c) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }

    for (int i = 0; i < a->height; i++) {
        for (int j = 0; j < a->width; j++) {
            c->data[i * a->width + j] = a->data[i * a->width + j] + b->data[i * a->width + j];
        }
    }

    return c;
}

matrix* dot_product_matrixes(const matrix* a, const matrix* b) {
    if (!a || !b) {
        fprintf(stderr, "null reference.\n");
        return NULL;
    }
    if (a->width != b->height) {
        fprintf(stderr, "A's columns must equal B's height.\n");
        return NULL;
    };
    matrix* c = create_matrix(a->height, b->width);
    if (!c) {
        fprintf(stderr, "out of memory.\n");
        return NULL;
    }

    for (int i = 0; i < c->height; i++) {
        for (int j = 0; j < c->width; j++) {
            for (int k = 0; k < a->width; k++) {
                double a_element = a->data[i * a->width + k];
                double b_element = b->data[k * b->width + j];
                c->data[i * c->width + j] += a_element * b_element;
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
    if (input->height != input->width) {
        fprintf(stderr, "matrix must be square.\n");
        return NULL;
    }

    int n = input->height;
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

        // Make the other height contain 0s in the current column
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
