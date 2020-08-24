#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

typedef struct 
{
    int rows;
    int cols;
    double **matrix;
} Matrix;

Matrix *create_matrix(int rows, int cols, const double mat[rows][cols]);
void print_matrix(Matrix *matrix);
bool is_null(Matrix *matrix);
int transpose(Matrix *a, Matrix *result);
int multiply(Matrix *a, Matrix *b, Matrix *result);
int multiply_transposed(Matrix *a, Matrix *b_t, Matrix *result);
int add(Matrix *a, Matrix *b);
int subtract(Matrix *a, Matrix *b);
int scalar_multiply(Matrix *matrix, double a);
int scalar_add(Matrix *matrix, double a);
int apply(Matrix *a, Matrix *result, double (*fn)(double));
int hadamard(Matrix *a, Matrix *b, Matrix *result);
int delete(Matrix *a);

#endif /* MATRIX_H */