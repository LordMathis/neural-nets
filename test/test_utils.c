#include "../lib/matrix.h"
#include "../lib/utils.h"
#include "test.h"
#include <stdlib.h>

static int test_vectorize()
{
    // Setup
    int res = 0;
    double mat[15][1][1];
    for (int i = 0; i < 15; i++)
    {
        mat[i][0][0] = i;
    }   

    Matrix **a = (Matrix**) malloc (sizeof (Matrix*) * 15);
    for (int i = 0; i < 15; i++)
    {
        a[i] = create_matrix(1,1,mat[i]);
    }

    vectorize(a, 15, 15);

    // Test
    for (int i = 0; i < 15; i++)
    {
        if (is_null(a[i]))
        {
            res += fail(__func__, "Vectorized matrix is null");
        }

        if (a[i]->rows != 15 || a[i]->cols != 1)
        {
            res += fail(__func__, "Wrong vectorized matrix dimensions");
        }

        for (int j = 0; j < 15; j++)
        {
            if ((i == j && a[i]->matrix[j][0] != 1) || (i != j && a[i]->matrix[j][0] != 0))
            {
                res += fail(__func__, "Wrong vectorized matrix values");
            }            
        }        
    }

    // Cleanup
    for (int i = 0; i < 15; i++)
    {
        delete_matrix(a[i]);
    }
    free(a);

    return eval_test_result(__func__, res); 
}

static int test_normalize()
{
    // Setup
    int res = 0;

    double mat[3][3][3];
    Matrix **a = (Matrix**) malloc (sizeof (Matrix*) * 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mat[0][i][j] = 1;
            mat[1][i][j] = 2;
            mat[2][i][j] = 3;
        }        
    }

    for (int i = 0; i < 3; i++)
    {
        a[i] = create_matrix(3,3, mat[i]);
    }

    normalize(a, 3, 4);

    // Test  
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[0]->matrix[i][j] != 0.25 || a[1]->matrix[i][j] != 0.5 || a[2]->matrix[i][j] != 0.75)
            {
                res += fail(__func__, "Wrong normalized matrix values");
            }
        }        
    }
    
    // Cleanup
    for (int i = 0; i < 3; i++)
    {
        delete_matrix(a[i]);
    }
    free(a);

    return eval_test_result(__func__, res); 
}

int test_utils()
{
    int res = 0;
    res += test_vectorize();
    res += test_normalize();
    return res;
}