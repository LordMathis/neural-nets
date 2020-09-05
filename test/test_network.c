#include "test.h"
#include "../lib/network.h"
#include "../lib/matrix.h"
#include <stdlib.h>

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

int test_predict()
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

int test_network()
{
    int res = 0;
    res += test_create_network();
    res += test_predict();
    return res;
}