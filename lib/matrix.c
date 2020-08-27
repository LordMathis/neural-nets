#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Matrix* create_matrix(int rows, int cols, const double mat[rows][cols])
{
    Matrix *matrix = (Matrix *) malloc (sizeof (Matrix));

    matrix->rows = rows;
    matrix->cols = cols;


    matrix->matrix = (double**) malloc (sizeof (double*) *rows);
    for (int i = 0; i < rows; i++)
    {
        matrix->matrix[i] = (double*) malloc (sizeof (double) *cols);
        for (int j = 0; j < cols; j++)
        {
            if (mat != NULL)
            {
                matrix->matrix[i][j] = mat[i][j];
            }
            else
            {
                matrix->matrix[i][j] = 0;
            }
        }
    }

    return matrix;
}

void print_matrix(Matrix *matrix)
{
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

bool is_null(Matrix *a)
{
    if (a == NULL || a->matrix == NULL)
    {
        return true;
    }

    return false;
}

int transpose(Matrix *a, Matrix *result)
{
    if (is_null(a) || is_null(result))
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            result->matrix[j][i] = a->matrix[i][j];
        }        
    }
    
    return 0;
}

int multiply(Matrix *a, Matrix *b, Matrix *result)
{
    if (is_null(a) || is_null(b) || is_null(result))
    {
        return -1;
    }

    if (a->cols != b->rows || a->rows != result->rows || b->cols != result->cols)
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
        {
            result->matrix[i][j] = 0;
            for (int k = 0; k < a->cols; k++)
            {
                result->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
            }            
        }        
    }

    return 0;
}

int multiply_transposed(Matrix *a, Matrix *b_t, Matrix *result)
{
    if (is_null(a) || is_null(b_t) || is_null(result))
    {
        return -1;
    }

    if (a->cols != b_t->cols || a->rows != result->rows || b_t->rows != result->cols)
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < b_t->rows; j++)
        {
            result->matrix[i][j] = 0;
            for (int k = 0; k < a->cols; k++)
            {
                result->matrix[i][j] += a->matrix[i][k] * b_t->matrix[j][k];
            }            
        }        
    }

    return 0;
}

int add(Matrix *a, Matrix *b)
{
    if (is_null(a) || is_null(b))
    {
        return -1;
    }

    if (a->rows != b->rows || a->cols != b->cols)
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            a->matrix[i][j] += b->matrix[i][j];
        }        
    }

    return 0;
}

int subtract(Matrix *a, Matrix *b)
{
    if (is_null(a) || is_null(b))
    {
        return -1;
    }

    if (a->rows != b->rows || a->cols != b->cols)
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            a->matrix[i][j] -= b->matrix[i][j];
        }        
    }

    return 0;
}

int scalar_multiply(Matrix *a, double x)
{
    if (is_null(a))
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            a->matrix[i][j] *= x;
        }        
    }  

    return 0;  
}

int scalar_add(Matrix *a, double x) {
    if (is_null(a))
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            a->matrix[i][j] += x;
        }        
    }

    return 0;
}

int apply(Matrix *a, Matrix *result, double (*fn)(double))
{
    if (is_null(result))
    {
        result = a;
    }
    else if (a->rows != result->rows || a->cols != result->cols)
    {
        return -1;
    }    
    
    if (is_null(a))
    {
        return -1;
    }

    if (fn == NULL)
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            result->matrix[i][j] = fn(a->matrix[i][j]);
        }        
    }

    return 0;
}

int hadamard(Matrix *a, Matrix *b, Matrix *result)
{
    if (is_null(a) || is_null(b))
    {
        return -1;
    }

    if (a->rows != b->rows || a->cols != b->cols || a->rows != result->rows || a->cols != result->cols)
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            result->matrix[i][j] = a->matrix[i][j] * b->matrix[i][j];
        }        
    }

    return 0;    
}

int argmax(Matrix *a)
{
    int max = 0;

    if (a->rows == 1)
    {
        for (int i = 0; i < a->cols; i++)
        {
            if (a->matrix[0][i] > a->matrix[0][max])
            {
                max = i;
            }
        }        
    }
    else if (a->cols == 1)
    {
        for (int i = 0; i < a->rows; i++)
        {
            if (a->matrix[i][0] > a->matrix[max][0])
            {
                max = i;
            }
        }   
    }
    else
    {
        max = -1;
    }

    return max;    
}

int reset_matrix(Matrix *a)
{
    if (is_null(a))
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            a->matrix[i][j] = 0;
        }        
    }

    return 0;    
}

int delete(Matrix *a)
{
    if (is_null(a))
    {
        return -1;
    }

    for (int i = 0; i < a->rows; i++)
    {
        free(a->matrix[i]);
    }

    free(a->matrix);
    free(a);
    
    return 0;
}

