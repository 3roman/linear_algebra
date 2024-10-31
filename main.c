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
    matrix *scaled = scale_matrix(neo, 10);
    matrix *transposed = transpose_matrix(neo);
    matrix *sum = add_matrixes(neo, neo);
    matrix *product = dot_product_matrixes(neo, transposed);

    matrix *temp = create_matrix(2, 2);
    temp->data[0] = 4;
    temp->data[1] = 7;
    temp->data[2] = 2;
    temp->data[3] = 6;
    matrix *inversed = inverse_matrix(temp);

    puts("\noriginal matrix:");
    print_matrix(neo, 8);
    puts("\nscaled matrix:");
    print_matrix(scaled, 8);
    puts("\ntransposed matrix:");
    print_matrix(transposed, 8);
    puts("\nsum:");
    print_matrix(sum, 8);
    puts("\nproduct:");
    print_matrix(product, 8);
    puts("\ninversed matrix:");
    print_matrix(inversed, 8);

    free_matrix(neo);
    free_matrix(scaled);
    free_matrix(transposed);
    free_matrix(inversed);
    free_matrix(sum);
    free_matrix(product);
    free_matrix(temp);

    return 0;
}