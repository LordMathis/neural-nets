#include "test.h"
#include "../lib/network.h"
#include "../lib/matrix.h"
#include <stdlib.h>
#include <stdio.h>


static double f(double num)
{
    return num;
}

static int test_create_network()
{
    int res = 0;

    int input_size = 10;
    int num_layers = 3;
    int layers[] = {30,20,10};

    Activation *sigmoid = create_sigmoid_activation();
    Network *network = create_network(input_size, num_layers, layers, sigmoid);

    if (network->num_layers != num_layers)
    {
        res += fail(__func__, "Number of layers do not match");
    }

    if (network == NULL || network->layers == NULL)
    {
        res += fail(__func__, "Network is null");
    }

    for (int i = 0; i < num_layers; i++)
    {
        if (network->layers[i] == NULL || network->layers[i]->num_neurons != layers[i])
        {
            res += fail(__func__, "Network has wrong layers");
        }
    }

    delete_network(network);
    delete_activation(sigmoid);
    return eval_test_result(__func__, res);
}

static int test_predict()
{
    int res = 0;

    int input_size = 10;
    int num_layers = 3;
    int layers[] = {30,20,10};

    Activation *sigmoid = create_sigmoid_activation();
    Network *network = create_network(input_size, num_layers, layers, sigmoid);

    double input_mat[10][1] =  {{1},{1},{1},{1},{1},{1},{1},{1},{1},{1}};
    Matrix *input = create_matrix(10, 1, input_mat);

    Matrix *result = predict(network, input);

    if (is_null(result))
    {
        res += fail(__func__, "Result matrix should not be null");
    }

    if (!is_non_zero(result))
    {
        res += fail(__func__, "Result matrix should not 0");
    }

    free(input);
    delete_network(network);
    delete_activation(sigmoid);
    return eval_test_result(__func__, res);
}

static int test_init_training()
{
    // Setup
    int res = 0;

    int input_size = 10;
    int num_layers = 3;
    int layers[] = {30,20,10};

    Activation *sigmoid = create_sigmoid_activation();
    Network *network = create_network(input_size, num_layers, layers, sigmoid);

    Matrix **delta_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);
    Matrix **temp_delta_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **delta_bias = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **deltas = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **temp_deltas = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers -1);
    Matrix **transposed_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers - 1);

    init_training(
        network,
        deltas,
        temp_deltas,
        delta_weights,
        temp_delta_weights,
        transposed_weights,
        delta_bias
    );

    // Test
    // TODO: Fix this!

    int test_layers[] = {10,30,20,10};
    for (int i = 1; i < num_layers + 1; i++)
    {
        int rows = test_layers[i];
        int cols = test_layers[i-1];

        if ((delta_weights[i-1]->rows != rows) || (delta_weights[i-1]->cols != cols)) {
            res += fail(__func__, "Delta weights matrix has wrong dimensions");
        }

        if (temp_delta_weights[i-1]->rows != rows || temp_delta_weights[i-1]->cols != cols) {
            res += fail(__func__, "Temp delta weights matrix has wrong dimensions");
        }

        if (i>1)
        {
            if (transposed_weights[i-2]->rows != cols || transposed_weights[i-2]->cols != rows) {
                res += fail(__func__, "Transposed weights matrix has wrong dimensions");
            }
        }

        if (delta_bias[i-1]->rows != rows || delta_bias[i-1]->cols != 1) {
            res += fail(__func__, "Delta bias matrix has wrong dimensions");
        }

        if (deltas[i-1]->rows != rows || deltas[i-1]->cols != 1) {
            res += fail(__func__, "Deltas matrix has wrong dimensions");
        }

        if (i>1)
        {
            if (temp_deltas[i-2]->rows != cols || temp_deltas[i-2]->cols != 1) {
                res += fail(__func__, "Temp deltas matrix has wrong dimensions");
            }
        }
    }
    return eval_test_result(__func__, res);
}

int test_network()
{
    int res = 0;
    res += test_create_network();
    res += test_predict();
    res += test_init_training();
    return res;
}