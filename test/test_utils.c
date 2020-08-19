#include <stdbool.h>
#include <stdio.h>
#include "test_utils.h"
#include "../lib/matrix.h"

int fail(const char *test_name, const char *message)
{
    RED_COLOR;
    printf("%s %s\n", test_name, message);
    RESET_COLOR;
    return -1;
}

int eval_test_result(const char *test_name, int result)
{
    if (result<0) {
        RED_COLOR;
        printf("%s\n", test_name);
        RESET_COLOR;
    } else {
        GREEN_COLOR;
        printf("%s\n", test_name);
        RESET_COLOR;
    }

    return result;
}

bool is_non_zero(Matrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            if (matrix->matrix[i][j] != 0)
            {
                return true;
            }
        }        
    }
    return false;    
}