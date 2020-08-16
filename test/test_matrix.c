#include "../lib/matrix.h"
#include "test.h"
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
    int a_rows = 3;
    int a_cols = 2;
    const double a_mat[3][2] = {{2,1}, {3,2}, {5,3}};
    Matrix *a_matrix = init_matrix(a_rows, a_cols, a_mat);

    int b_rows = 2;
    int b_cols = 3;
    const double b_mat[2][3] = {{5,0,3}, {4,1,7}};

    Matrix *b_matrix = init_matrix(b_rows, b_cols, b_mat);

    int res_rows = 3;
    int res_cols = 3;
    const double res_mat[3][3] = {
        {14.00, 1.00, 13.00 },
        {23.00, 2.00, 23.00 },
        {37.00, 3.00, 36.00 }
    };

    Matrix *res_matrix = init_matrix(res_rows, res_cols, NULL);
    multiply(a_matrix, b_matrix, res_matrix);

    if (res_matrix->matrix == NULL)
    {
        printf("Test multiply failed! Matrix is NULL");
        return -1;
    }

    for (int i = 0; i < res_rows; i++)
    {
        for (int j = 0; j < res_cols; j++)
        {
            if (res_matrix->matrix[i][j] != res_mat[i][j])
            {
                printf("Test multiply failed! Matrix has wrong values");
                return -1;
            }
        }        
    }

    delete(a_matrix);
    delete(b_matrix);
    delete(res_matrix);

    printf("Test multiply passed");
    return 0;
}

static int test_scalar_multiply()
{
    // TODO:
    return 0;
}

static int test_scalar_add()
{
    // TODO:
    return 0;
}

static int test_add()
{
    // TODO:
    return 0;
}

static int test_apply()
{
    // TODO:
    return 0;
}

static int test_delete()
{
    // TODO:
    return 0;
}


int test_matrix()
{
    int res;
    res += test_create_matrix();
    res += test_transpose();
    res += test_is_null();
    res += test_multiply();
    res += test_scalar_multiply();
    res += test_scalar_add();
    res += test_add();
    res += test_apply();
    res += test_delete();

    if (res < 0)
    {
        return -1;
    }

    return 0;
}