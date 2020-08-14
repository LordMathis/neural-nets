#include "./lib/matrix.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    int a_rows = 3;
    int a_cols = 2;
    const float a_mat[3][2] = {{2,1}, {3,2}, {5,3}};

    Matrix *a_matrix = init_matrix(a_rows, a_cols, a_mat);
    print_matrix(a_matrix);

    printf("\n");

    int b_rows = 2;
    int b_cols = 3;
    const float b_mat[2][3] = {{5,0,3}, {4,1,7}};

    Matrix *b_matrix = init_matrix(b_rows, b_cols, b_mat);
    print_matrix(b_matrix);

    printf("\n");

    int res_rows = 3;
    int res_cols = 3;
    Matrix *res_matrix = init_matrix(res_rows, res_cols, NULL);
    print_matrix(res_matrix);

    printf("\n");

    multiply(a_matrix, b_matrix, res_matrix);
    print_matrix(res_matrix);
}