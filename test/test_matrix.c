#include "../lib/matrix.h"
#include <stdlib.h>
#include <stdio.h>

static int test_create_matrix()
{
    int rows = 3;
    int cols = 3;

    double mat[3][3] = {{1,1,1}, {2,2,2}, {3,3,3}};

    Matrix *matrix = create_matrix(rows, cols, mat);

    if (matrix == NULL || matrix->matrix == NULL)
    {
        printf("Test create matrix failed! Matrix is NULL");
        return -1;
    }

    if (matrix->rows != rows || matrix->cols != cols)
    {
        printf("Test create matrix failed! Matrix has wrong dimensions");
        return -1;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix->matrix[i][j] != i)
            {
                printf("Test create matrix failed! Matrix has wrong values");
                return -1;
            }
        }        
    }

    delete(matrix);

    printf("Test create matrix passed");
    return 0;
}

static int test_transpose()
{
    int rows = 2;
    int cols = 4;

    double mat[2][4] = {
        {1,2},
        {3,4},
        {5,6},
        {6,7}
    };

    Matrix *matrix = create_matrix(rows, cols, mat);
    Matrix *transposed = create_matrix(cols, rows, NULL);

    transpose(matrix, transposed);

    if (transposed == NULL || transposed->matrix == NULL)
    {
        printf("Test transpose matrix failed! Transposed matrix is NULL");
        return -1;
    }

    if (transposed->rows != cols || transposed->cols != rows)
    {
        printf("Test transposed matrix failed! Transposed matrix has wrong dimensions");
        return -1;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix->matrix[i][j] != transposed->matrix[j][i])
            {
                printf("Test transpose matrix failed! Transposed matrix has wrong values");
                return -1;
            }
        }        
    }

    delete(matrix);
    delete(transposed);

    printf("Test transpose matrix passed");
    return 0;
}

static int test_is_null()
{
    Matrix *matrix;

    if(!is_null(matrix))
    {
        printf("Test is null failed");
        return -1;
    }

    matrix = create_matrix(1,1,NULL);
    if(is_null(matrix))
    {
        printf("Test is null failed");
        return -1;
    }

    double **temp = matrix->matrix;
    matrix->matrix = NULL;

    if(!is_null(matrix))
    {
        printf("Test is null failed");
        return -1;
    }

    matrix->matrix = temp;
    delete(matrix);

    printf("Test is null passed");
    return 0;
}

static int test_multiply()
{
    
}

static int test_scalar_multiply();
static int test_scalar_add();
static int test_add();
static int test_apply();
static int test_delete();

int test_matrix()
{
    int res;
    res = test_create_matrix();
    if (res == -1)
    {
        printf("Test matrix failed");
        return -1;
    }
    res = test_transpose();
    if (res == -1)
    {
        printf("Test matrix failed");
        return -1;
    }
    res = test_is_null();
    if (res == -1)
    {
        printf("Test matrix failed");
        return -1;
    }
    res = test_multiply();
    if (res == -1)
    {
        printf("Test matrix failed");
        return -1;
    }
    res = test_scalar_multiply();
    if (res == -1)
    {
        printf("Test matrix failed");
        return -1;
    }
    res = test_scalar_add();
    if (res == -1)
    {
        printf("Test matrix failed");
        return -1;
    }
    res = test_add();
    if (res == -1)
    {
        printf("Test matrix failed");
        return -1;
    }
    res = test_apply();
    if (res == -1)
    {
        printf("Test matrix failed");
        return -1;
    }
    res = test_delete();
    if (res == -1)
    {
        printf("Test matrix failed");
        return -1;
    }
}