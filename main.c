#include <stdio.h>

#include "matrix.h"

int main() {
    int m = 3, n = 4;
    matrix *neo = create_matrix(m, n);
    int counter = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            neo->data[i * n + j] = counter++;
        }
    }
    neo->data[6] = 7;
    matrix *scaled_matrix = scale_matrix(neo, 2);
    matrix *spider = transpose_matrix(scaled_matrix);
    matrix *product = dot_product_matrixes(neo, spider);
    print_matrix(neo);
    print_matrix(spider);
    print_matrix(product);

    free_matrix(neo);
    free_matrix(spider);
    free_matrix(scaled_matrix);
    free_matrix(product);

    return 0;
}