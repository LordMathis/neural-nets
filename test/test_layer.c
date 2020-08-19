#include "test.h"
#include "test_utils.h"
#include "../lib/layer.h"
#include "../lib/matrix.h"
#include <stdbool.h>

static double activate(double x)
{
    return x;
}

static bool is_non_zero(Matrix *matrix)
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

static int test_create_layer()
{
    // Setup
    int layer_size = 20;
    int input_size = 30;

    double (*act)(double) = &activate;

    Layer *layer = create_layer(layer_size, input_size, act);

    //Tests
    if (layer->num_neurons != layer_size)
    {
        return log_failure(__func__, "Wrong layer size");
    }

    if (layer->activation_fn != act)
    {
        return log_failure(__func__, "Wrong layer activation function");
    }

    if (is_null(layer->weights) || is_null(layer->bias) || is_null(layer->neurons))
    {
        return log_failure(__func__, "Layer cannot be null");
    }

    if (layer->weights->rows != input_size || layer->weights->cols != layer_size)
    {
        return log_failure(__func__, "Wrong weight matrix dimensions");
    }

    if (layer->bias->rows != layer_size || layer->bias->cols != 1)
    {
        return log_failure(__func__, "Wrong bias matrix dimensions");
    }

    if (layer->neurons->rows != layer_size || layer->neurons->cols != 1)
    {
        return log_failure(__func__, "Wrong neurons matrix dimensions");
    }

    // Test if layer is initialized
    if (!is_non_zero(layer->weights) || !is_non_zero(layer->bias))
    {
        print_matrix(layer->weights);
        print_matrix(layer->bias);
        return log_failure(__func__, "Layer is not properly initialized");
    }

    // Cleanup
    delete_layer(layer);
    return log_success(__func__);
}

int test_layer_compute()
{
    int layer_size = 30;
    int input_size = 10;

    double (*act)(double) = &activate;

    Layer *layer = create_layer(layer_size, input_size, act);

    double mat[10][1] = {{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}};
    Matrix *input = create_matrix(input_size, 1, mat);

    layer_compute(layer, input);

    if (is_null(layer->neurons))
    {
        return log_failure(__func__, "Layer neurons cannot be null");
    }

    if (!is_non_zero(layer->neurons))
    {
        return log_failure(__func__, "Layer neurons should not be zero matrix");
    }

        // Cleanup
    delete_layer(layer);
    delete(input);
    return log_success(__func__);
}


int test_layer()
{
    int res = 0;
    res += test_create_layer();
    res += test_layer_compute();
    return res;
}