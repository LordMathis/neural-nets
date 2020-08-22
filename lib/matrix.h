#ifndef MATRIX_H
#define MATRIX_H

typedef struct 
{
    int rows;
    int cols;
    double **matrix;
} Matrix;

Matrix *create_matrix(int rows, int cols, const double mat[rows][cols]);
void print_matrix(Matrix *matrix);
int transpose(Matrix *a, Matrix *result);
int is_null(Matrix *matrix);
int multiply(Matrix *a, Matrix *b, Matrix *result);
int scalar_multiply(Matrix *matrix, double a);
int scalar_add(Matrix *matrix, double a);
int add(Matrix *a, Matrix *b);
int subtract(Matrix *a, Matrix *b);
int hadamard(Matrix *a, Matrix *b, Matrix *result);
int apply(Matrix *a, Matrix *result, double (*fn)(double));
int delete(Matrix *a);

#endif /* MATRIX_H */