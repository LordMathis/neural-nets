#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void print_matrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++)
    {
        printf("[ ");
        for (int j = 0; j < matrix->cols; j++)
        {
            printf("%.2f ", matrix->matrix[i][j]);
        }
        printf("]\n");
    }    
}

Matrix* init_matrix(int rows, int cols, const double mat[rows][cols]) {
    Matrix *matrix = (Matrix *) malloc (sizeof (Matrix));

    matrix->rows = rows;
    matrix->cols = cols;


    matrix->matrix = (double**) malloc (sizeof (double *) * rows);
    for (int i = 0; i < rows; i++) {
        matrix->matrix[i] = (double*) malloc (sizeof (double) * cols);
        for (int j = 0; j < cols; j++) {
            if (mat != NULL) {
                matrix->matrix[i][j] = mat[i][j];
            }
            else {
                matrix->matrix[i][j] = 0;
            }
        }
    }

    return matrix;
}

int multiply(Matrix *a, Matrix *b, Matrix *result) {

    if (is_null(a) == -1 || is_null(b) == -1) {
        return -1;
    }

    if (is_null(result)) {
        result = init_matrix(a->rows, b->cols, NULL);
    }

    if (a->cols != b->rows || a->rows != result->rows || b->cols != result->cols) {
        return -1;
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            result->matrix[i][j] = 0;
            for (int k = 0; k < a->cols; k++) {
                result->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
            }            
        }        
    }

    return 0;
}

int scalar_multiply(Matrix *matrix, double a) {
    if (is_null(matrix) == -1) {
        return -1;
    }

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            matrix->matrix[i][j] *= a;
        }        
    }  

    return 0;  
}

int scalar_add(Matrix *matrix, double a) {
    if (is_null(matrix) == -1) {
        return -1;
    }

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            matrix->matrix[i][j] += a;
        }        
    }

    return 0;
}

int is_null(Matrix *matrix) {
    if (matrix == NULL || matrix->matrix == NULL) {
        return -1;
    }

    return 0;
}

