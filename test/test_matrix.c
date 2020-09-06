#include "../lib/matrix.h"
#include "test.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static bool is_equal(Matrix *matrix, int rows, int cols, const double mat[rows][cols])
{
    if (matrix->rows != rows || matrix->cols != cols)
    {
        return false;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix->matrix[i][j] != mat[i][j])
            {
                return false;
            }
        }        
    }

    return true;
}

static int test_create_matrix()
{
    // Setup
    int res = 0;


    int rows = 3;
    int cols = 3;

    double mat[3][3] = {{1,1,1}, {2,2,2}, {3,3,3}};

    Matrix *matrix = create_matrix(rows, cols, mat);

    // Test
    if (is_null(matrix))
    {
        res+=fail(__func__, "Matrix is NULL");
    }

    if (!is_equal(matrix, rows, cols, mat))
    {
        res+=fail(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete_matrix(matrix);
   
    return eval_test_result(__func__, res);
}

static int test_is_null()
{
    // Setup
    int res = 0;

    Matrix *matrix = NULL;

    // Test null pointer
    if(!is_null(matrix))
    {
        res+=fail(__func__, "Matrix should be null");
    }

    // Test non null matrix
    matrix = create_matrix(1,1,NULL);
    if(is_null(matrix))
    {
        res+=fail(__func__, "Matrix should not be null");

    }

    // Test null array
    double **temp = matrix->matrix;
    matrix->matrix = NULL;

    if(!is_null(matrix))
    {
        res+=fail(__func__, "Matrix should be null");

    }

    // Cleanup
    matrix->matrix = temp;
    delete_matrix(matrix);
   
    return eval_test_result(__func__, res);
}

static int test_transpose()
{
    // Setup
    int res = 0;

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
        res+=fail(__func__, "Transposed matrix is NULL\n");
    }

    if (!is_equal(transposed, cols, rows, transposed_mat))

    // Cleanup

    delete_matrix(matrix);
    delete_matrix(transposed);
   
    return eval_test_result(__func__, res);
}

static int test_multiply()
{
    // Setup
    int res = 0;

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
        res+=fail(__func__, "Mismatched dimension should not be multiplied");
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
        res+=fail(__func__, "Matrix should not be null");
    }

    if (!is_equal(res_matrix, res_rows, res_cols, res_mat))
    {
        res+=fail(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete_matrix(a_matrix);
    delete_matrix(b_matrix);
    delete_matrix(c_matrix);
    delete_matrix(res_wrong_dims_mat);
    delete_matrix(res_matrix);
   
    return eval_test_result(__func__, res);
}

static int test_multiply_transposed()
{
    // Setup
    int res = 0;

    int a_rows = 3;
    int a_cols = 2;
    const double a_mat[3][2] = {{2,1}, {3,2}, {5,3}};
    Matrix *a_matrix = create_matrix(a_rows, a_cols, a_mat);

    int b_rows = 3;
    int b_cols = 2;
    const double b_mat[3][2] = {{5,4}, {0,1}, {3,7}}; // Transposed: {{5,0,3}, {4,1,7}}
    Matrix *b_matrix = create_matrix(b_rows, b_cols, b_mat);

    int c_rows = 4;
    int c_cols = 5;
    Matrix *c_matrix = create_matrix(c_rows, c_cols, NULL);

    // Test multiply wrong dimensions
    Matrix *res_wrong_dims_mat = create_matrix(a_cols, c_rows, NULL);
    int res_wrong_dims = multiply_transposed(a_matrix, c_matrix, res_wrong_dims_mat);
    if (res_wrong_dims != -1)
    {
        res+=fail(__func__, "Mismatched dimension should not be multiplied");
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
    multiply_transposed(a_matrix, b_matrix, res_matrix);

    if (is_null(res_matrix))
    {
        res+=fail(__func__, "Matrix should not be null");
    }

    if (!is_equal(res_matrix, res_rows, res_cols, res_mat))
    {
        res+=fail(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete_matrix(a_matrix);
    delete_matrix(b_matrix);
    delete_matrix(c_matrix);
    delete_matrix(res_wrong_dims_mat);
    delete_matrix(res_matrix);
   
    return eval_test_result(__func__, res);
}

static int test_add()
{
    // Setup
    int res = 0;

    int rows = 3;
    int cols = 2;
    const double a_mat[3][2] = {{2,1}, {3,2}, {5,3}};
    Matrix *a_matrix = create_matrix(rows, cols, a_mat);

    const double b_mat[3][2] = {{5,0}, {4,3}, {4,1}};
    Matrix *b_matrix = create_matrix(rows, cols, b_mat);

    int c_rows = 4;
    int c_cols = 5;
    Matrix *c_matrix = create_matrix(c_rows, c_cols, NULL);

    // Test add wrong dimensions
    int res_wrong_dims = add(a_matrix, c_matrix);
    if (res_wrong_dims != -1)
    {
        res+=fail(__func__, "Sum of mismatched dimension matrices should not be possible");
    }

    // Test add correct dimensions
    const double res_mat[3][2] = {
        {7.00, 1.00 },
        {7.00, 5.00 },
        {9.00, 4.00 }
    };

    add(a_matrix, b_matrix);

    if (is_null(a_matrix))
    {
        res+=fail(__func__, "Matrix should not be null");
    }

    if (!is_equal(a_matrix, rows, cols, res_mat))
    {
        res+=fail(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete_matrix(a_matrix);
    delete_matrix(b_matrix);
    delete_matrix(c_matrix);
   
    return eval_test_result(__func__, res);
}

static int test_subtract()
{
    // Setup
    int res = 0;

    int rows = 3;
    int cols = 2;
    const double a_mat[3][2] = {{2,1}, {3,2}, {5,3}};
    Matrix *a_matrix = create_matrix(rows, cols, a_mat);

    const double b_mat[3][2] = {{5,0}, {4,3}, {4,1}};
    Matrix *b_matrix = create_matrix(rows, cols, b_mat);

    int c_rows = 4;
    int c_cols = 5;
    Matrix *c_matrix = create_matrix(c_rows, c_cols, NULL);

    // Test add wrong dimensions
    int res_wrong_dims = subtract(a_matrix, c_matrix);
    if (res_wrong_dims != -1)
    {
        res+=fail(__func__, "Subtraction of mismatched dimension matrices should not be possible");
    }

    // Test add correct dimensions
    const double res_mat[3][2] = {
        {-3.00, 1.00 },
        {-1.00, -1.00 },
        {1.00, 2.00 }
    };

    subtract(a_matrix, b_matrix);

    if (is_null(a_matrix))
    {
        res+=fail(__func__, "Matrix should not be null");
    }

    if (!is_equal(a_matrix, rows, cols, res_mat))
    {
        res+=fail(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete_matrix(a_matrix);
    delete_matrix(b_matrix);
    delete_matrix(c_matrix);
   
    return eval_test_result(__func__, res);
}

static int test_scalar_multiply()
{
    // Setup
    int res = 0;

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
        res+=fail(__func__, "Matrix should not be null");
    }

    if (!is_equal(a, rows, cols, res_mat))
    {
        res+=fail(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete_matrix(a); 
   
    return eval_test_result(__func__, res);
}

static int test_scalar_add()
{
    // Setup
    int res = 0;

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
        res+=fail(__func__, "Matrix should not be null");
    }

    if (!is_equal(a, rows, cols, res_mat))
    {
        res+=fail(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete_matrix(a);   
   
    return eval_test_result(__func__, res);
}

static double square(double num)
{
    return num*num;
}

static int test_apply()
{
    // Setup
    int res = 0;

    double (*square_ptr)(double) = &square;

    int rows = 2;
    int cols = 2;
    const double a_mat[2][2] = {{1,2}, {3,4}};
    Matrix *a_matrix = create_matrix(rows, cols, a_mat);

    const double res_mat[2][2] = {{1,4}, {9, 16}};

    apply(a_matrix, NULL, square_ptr);

    if (is_null(a_matrix))
    {
        res+=fail(__func__, "Matrix should not be null");
    }

    if (!is_equal(a_matrix, rows, cols, res_mat))
    {
        res+=fail(__func__, "Wrong matrix dimensions or values");
    }

    delete_matrix(a_matrix);
    square_ptr = NULL;
   
    return eval_test_result(__func__, res);
}

static int test_hadamard()
{
    // Setup
    int res = 0;

    int a_rows = 3;
    int a_cols = 2;
    const double a_mat[3][2] = {{2,1}, {3,2}, {5,3}};
    Matrix *a_matrix = create_matrix(a_rows, a_cols, a_mat);

    int b_rows = 3;
    int b_cols = 2;
    const double b_mat[3][2] = {{5,0}, {3,4}, {1,7}};
    Matrix *b_matrix = create_matrix(b_rows, b_cols, b_mat);

    int c_rows = 4;
    int c_cols = 5;
    Matrix *c_matrix = create_matrix(c_rows, c_cols, NULL);

    // Test multiply wrong dimensions
    Matrix *res_wrong_dims_mat = create_matrix(a_cols, c_rows, NULL);
    int res_wrong_dims = hadamard(a_matrix, c_matrix, res_wrong_dims_mat);
    if (res_wrong_dims != -1)
    {
        res+=fail(__func__, "Mismatched dimension should not be multiplied");
    }

    // Test multiply correct dimensions
    int res_rows = 3;
    int res_cols = 2;
    const double res_mat[3][2] = {
        {10.00, 0.00},
        {9.00, 8.00},
        {5.00, 21.00}
    };

    Matrix *res_matrix = create_matrix(res_rows, res_cols, NULL);
    hadamard(a_matrix, b_matrix, res_matrix);

    if (is_null(res_matrix))
    {
        res+=fail(__func__, "Matrix should not be null");
    }

    if (!is_equal(res_matrix, res_rows, res_cols, res_mat))
    {
        res+=fail(__func__, "Wrong matrix dimensions or values");
    }

    // Cleanup
    delete_matrix(a_matrix);
    delete_matrix(b_matrix);
    delete_matrix(c_matrix);
    delete_matrix(res_wrong_dims_mat);
    delete_matrix(res_matrix);
   
    return eval_test_result(__func__, res);
}

static int test_argmax()
{
    // Setup
    int res = 0;
    double mat[10][1];
    for (int i = 0; i < 10; i++)
    {
        mat[i][0] = (double) i / 10;
    }

    Matrix *a = create_matrix(10, 1, mat);

    // Tests
    int arg = argmax(a);

    if (arg != 9)
    {
        res+=fail(__func__, "Wrong argmax result");
    }

    int index = 4;
    a->matrix[index][0] += 10;

    arg = argmax(a);

    if (arg != index)
    {
        res+=fail(__func__, "Wrong argmax result");
    }

    // Cleanup
    delete_matrix(a);
    return eval_test_result(__func__, res);
}

int test_matrix()
{
    int res = 0;
    res += test_create_matrix();
    res += test_is_null();
    res += test_transpose();
    res += test_multiply();
    res += test_multiply_transposed();
    res += test_add();
    res += test_subtract();
    res += test_scalar_multiply();
    res += test_scalar_add();
    res += test_apply();
    res += test_hadamard();
    res += test_argmax();

    return res;
}