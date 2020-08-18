#include "../lib/matrix.h"
#include "test.h"
#include "test_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static int is_equal(Matrix *matrix, int rows, int cols, const double mat[rows][cols])
{
    if (matrix->rows != rows || matrix->cols != cols)
    {
        return 0;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix->matrix[i][j] != mat[i][j])
            {
                return 0;
            }
        }        
    }

    return 1;
}

static int test_create_matrix()
{
    // Setup
    int rows = 3;
    int cols = 3;

    double mat[3][3] = {{1,1,1}, {2,2,2}, {3,3,3}};

    Matrix *matrix = create_matrix(rows, cols, mat);

    // Test
    if (is_null(matrix))
    {
        return log_failure(__func__, "Matrix is NULL");
    }

    if (!is_equal(matrix, rows, cols, mat))
    {
        return log_failure(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete(matrix);
    return log_success(__func__);
}

static int test_transpose()
{
    // Setup
    int rows = 2;
    int cols = 4;

    double mat[2][4] = {
        {1,2,3,4},
        {5,6,6,7}
    };

    double transposed_mat[4][2] = {
        {1,5},
        {2,6},
        {3,6},
        {4,7}
    };

    Matrix *matrix = create_matrix(rows, cols, mat);
    Matrix *transposed = create_matrix(cols, rows, NULL);

    transpose(matrix, transposed);

    // Test
    if (is_null(transposed))
    {
        return log_failure(__func__, "Transposed matrix is NULL\n");
    }

    if (!is_equal(transposed, cols, rows, transposed_mat))

    // Cleanup

    delete(matrix);
    delete(transposed);

    return log_success(__func__);
}

static int test_is_null()
{
    // Setup
    Matrix *matrix = NULL;

    // Test null pointer
    if(!is_null(matrix))
    {
        return log_failure(__func__, "Matrix should be null");
    }

    // Test non null matrix
    matrix = create_matrix(1,1,NULL);
    if(is_null(matrix))
    {
        return log_failure(__func__, "Matrix should not be null");

    }

    // Test null array
    double **temp = matrix->matrix;
    matrix->matrix = NULL;

    if(!is_null(matrix))
    {
        return log_failure(__func__, "Matrix should be null");

    }

    // Cleanup
    matrix->matrix = temp;
    delete(matrix);

    return log_success(__func__);
}

static int test_multiply()
{
    // Setup
    int a_rows = 3;
    int a_cols = 2;
    const double a_mat[3][2] = {{2,1}, {3,2}, {5,3}};
    Matrix *a_matrix = create_matrix(a_rows, a_cols, a_mat);

    int b_rows = 2;
    int b_cols = 3;
    const double b_mat[2][3] = {{5,0,3}, {4,1,7}};
    Matrix *b_matrix = create_matrix(b_rows, b_cols, b_mat);

    int c_rows = 4;
    int c_cols = 5;
    Matrix *c_matrix = create_matrix(c_rows, c_cols, NULL);

    // Test multiply wrong dimensions
    Matrix *res_wrong_dims_mat = create_matrix(a_cols, c_rows, NULL);
    int res_wrong_dims = multiply(a_matrix, c_matrix, res_wrong_dims_mat);
    if (res_wrong_dims != -1)
    {
        return log_failure(__func__, "Mismatched dimension should not be multiplied");
    }

    // Test multiply correct dimensions
    int res_rows = 3;
    int res_cols = 3;
    const double res_mat[3][3] = {
        {14.00, 1.00, 13.00 },
        {23.00, 2.00, 23.00 },
        {37.00, 3.00, 36.00 }
    };

    Matrix *res_matrix = create_matrix(res_rows, res_cols, NULL);
    multiply(a_matrix, b_matrix, res_matrix);

    if (is_null(res_matrix))
    {
        return log_failure(__func__, "Matrix should not be null");
    }

    if (!is_equal(res_matrix, res_rows, res_cols, res_mat))
    {
        return log_failure(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete(a_matrix);
    delete(b_matrix);
    delete(res_matrix);

    return log_success(__func__);
}

static int test_scalar_multiply()
{
    // Setup
    int rows = 3;
    int cols = 3;
    const double a_mat[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    Matrix *a = create_matrix(rows, cols, a_mat);

    double x = 0.5;
    const double res_mat[3][3] = {{0.5,1,1.5}, {2,2.5,3}, {3.5,4,4.5}};
    scalar_multiply(a, x);

    // Test
    if (is_null(a))
    {
        return log_failure(__func__, "Matrix should not be null");
    }

    if (!is_equal(a, rows, cols, res_mat))
    {
        return log_failure(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete(a);    
    return log_success(__func__);
}

static int test_scalar_add()
{
    // Setup
    int rows = 3;
    int cols = 3;
    const double a_mat[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    Matrix *a = create_matrix(rows, cols, a_mat);

    double x = 10.5;
    const double res_mat[3][3] = {{11.5,12.5,13.5}, {14.5,15.5,16.5}, {17.5,18.5,19.5}};

    scalar_add(a, x);

    // Test
    if (is_null(a))
    {
        return log_failure(__func__, "Matrix should not be null");
    }

    if (!is_equal(a, rows, cols, res_mat))
    {
        return log_failure(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete(a);    
    return log_success(__func__);
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

int test_matrix()
{
    int res;
    res += test_create_matrix();
    res += test_transpose();
    res += test_is_null();
    res += test_multiply();
    res += test_scalar_multiply();
    res += test_scalar_add();
    // res += test_add();
    // res += test_apply();

    if (res < 0)
    {
        return -1;
    }

    return 0;
}