#include "test.h"
#include "../lib/layer.h"
#include "../lib/matrix.h"
#include "../lib/functions.h"
#include <stdbool.h>

static int test_create_layer()
{
    // Setup
    int res = 0;

    int layer_size = 20;
    int input_size = 30;

    Activation *sigmoid = create_sigmoid_activation();
    Layer *layer = create_layer(layer_size, input_size, sigmoid);

    //Tests
    if (layer->num_neurons != layer_size)
    {
        res+=fail(__func__, "Wrong layer size");
    }

    if (layer->activation != sigmoid)
    {
        res+=fail(__func__, "Wrong layer activation function");
    }

    if (is_null(layer->weights) || is_null(layer->bias) || is_null(layer->neurons))
    {
        res+=fail(__func__, "Layer cannot be null");
    }

    if (layer->weights->rows != layer_size || layer->weights->cols != input_size)
    {
        res+=fail(__func__, "Wrong weight matrix dimensions");
    }

    if (layer->bias->rows != layer_size || layer->bias->cols != 1)
    {
        res+=fail(__func__, "Wrong bias matrix dimensions");
    }

    if (layer->neurons->rows != layer_size || layer->neurons->cols != 1)
    {
        res+=fail(__func__, "Wrong neurons matrix dimensions");
    }

    // Test if layer is initialized
    if (!is_non_zero(layer->weights) || !is_non_zero(layer->bias))
    {
        print_matrix(layer->weights);
        print_matrix(layer->bias);
        res+=fail(__func__, "Layer is not properly initialized");
    }

    // Cleanup
    delete_layer(layer);
    delete_activation(sigmoid);
    return eval_test_result(__func__, res);
}

int test_layer_compute()
{
    int res = 0;

    int layer_size = 30;
    int input_size = 10;

    Activation *sigmoid = create_sigmoid_activation();
    Layer *layer = create_layer(layer_size, input_size, sigmoid);

    double mat[10][1] = {{1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}};
    Matrix *input = create_matrix(input_size, 1, mat);

    if (layer_compute(layer, input) < 0)
    {
        res+=fail(__func__, "Layer compute failed");
    }

    if (is_null(layer->neurons_act))
    {
        res+=fail(__func__, "Layer neurons cannot be null");
    }

    if (!is_non_zero(layer->neurons_act))
    {
        res+=fail(__func__, "Layer neurons should not be zero matrix");
    }

        // Cleanup
    delete_layer(layer);
    delete(input);
    delete_activation(sigmoid);
    return eval_test_result(__func__, res);
}


int test_layer()
{
    int res = 0;
    res += test_create_layer();
    res += test_layer_compute();
    return res;
}