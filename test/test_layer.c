#include "test.h"
#include "test_utils.h"
#include "../lib/layer.h"
#include "../lib/matrix.h"

static double activate(double x)
{
    return x;
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

    // Cleanup
    delete_layer(layer);
    return log_success(__func__);
}


int test_layer()
{
    int res = 0;
    res += test_create_layer();
    return res;
}