#include "layer.h"
#include "matrix.h"
#include "network.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Network* create_network(int input_size, int num_layers, int layers[], Activation *activation)
{
    Network *network = (Network *) malloc (sizeof (Network));
    network->num_layers = num_layers;

    network->layers = (Layer **) malloc (sizeof (Layer*) *num_layers);
    int prev_layer_size = input_size;
    for (int i = 0; i < num_layers; i++)
    {
        network->layers[i] = create_layer(layers[i], prev_layer_size, activation);
        prev_layer_size = layers[i];
    }
    
    return network;
}

int delete_network(Network *network)
{
    for (int i = 0; i < network->num_layers; i++)
    {
        delete_layer(network->layers[i]);
    }

    free(network->layers);
    free(network);
    network = NULL;

    return 0;
}

Matrix* predict(Network *network, Matrix *input)
{
    Matrix *layer_input = input;
    for (int i = 0; i < network->num_layers; i++)
    {
        Layer *layer = network->layers[i];
        int res = layer_compute(layer, layer_input);
        if (res < 0)
        {
            log_exception(__func__, "Exception during prediction");
        }
        layer_input = layer->neurons_act;
    }
    
    return layer_input;
}

static int init_training(
    Network *network,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias)
{
    for (int i = 0; i < network->num_layers; i++)
    {
        int rows = network->layers[i]->weights->rows;
        int cols = network->layers[i]->weights->cols;

        delta_weights[i] = create_matrix(rows, cols, NULL);
        temp_delta_weights[i] = create_matrix(rows, cols, NULL);

        if (i>0)
        {
            transposed_weights[i-1] = create_matrix(cols, rows, NULL);
            transpose(network->layers[i]->weights, transposed_weights[i-1]);
        }

        int bias_rows = network->layers[i]->bias->rows;
        int bias_cols = network->layers[i]->bias->cols;

        delta_bias[i] = create_matrix(bias_rows, bias_cols, NULL);
        deltas[i] = create_matrix(bias_rows, bias_cols, NULL);

        if (i>0)
        {
            temp_deltas[i-1] = create_matrix(cols, bias_cols, NULL);
        }
    }

    return 0;
}

static int backpropagate(
    Network *network,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias)
{
    int res;
    Layer *layer;
    Layer *prev_layer;

    for (int i = network->num_layers - 2; i >= 0; i--)
    {
        layer = network->layers[i];
        prev_layer = network->layers[i+1];

        // Compute new delta
        res = 0;
        res += apply(layer->neurons, NULL, layer->activation->fn_der);
        res += multiply(transposed_weights[i], deltas[i+1], temp_deltas[i]);
        res += hadamard(temp_deltas[i], layer->neurons, deltas[i]);
        if (res < 0)
        {
            log_exception(__func__, "Exception during delta calculation");
            return res;
        }

        // Compute delta weights
        res = 0;
        res += multiply_transposed(deltas[i], layer->neurons_act, temp_delta_weights[i]);
        res += add(delta_weights[i], temp_delta_weights[i]);
        if (res < 0)
        {
            log_exception(__func__, "Exception during delta weights calculation");
            return res;
        }


        // Compute delta bias
        res = add(delta_bias[i], deltas[i]);
        if (res < 0)
        {
            log_exception(__func__, "Exception during delta bias calculation");
            return res;
        }
    }      
}

static void cleanup(
    int network_length,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias)
{
        // Cleanup
    for (int i = 0; i < network_length; i++)
    {
        delete(deltas[i]);
        delete(delta_weights[i]);
        delete(temp_delta_weights[i]);
        delete(delta_bias[i]);

        if (i != network_length - 1) {
            delete(transposed_weights[i]);
            delete(temp_deltas[i]);
        }
    }
    free(deltas);
    free(temp_deltas);
    free(delta_weights);
    free(temp_delta_weights);
    free(transposed_weights);
    free(delta_bias);
}

static int reset(
    Network *network,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias)
{
    int res = 0;
    for (int i = 0; i < network->num_layers; i++)
    {
        res += reset_matrix(deltas[i]);
        res += reset_matrix(delta_weights[i]);
        res += reset_matrix(temp_delta_weights[i]);
        res += reset_matrix(delta_bias[i]);

        if (i != network->num_layers - 1) {
            res += reset_matrix(transposed_weights[i]);
            res += reset_matrix(temp_deltas[i]);
        }

        if (i != 0)
        {
            res += transpose(network->layers[i]->weights, transposed_weights[i-1]);
        }

        if (res < 0)
        {
            log_exception(__func__, "Exception during training temp objects reset");
            return res;
        }
    }    
}

int train(Network *network, Matrix **input_dataset, Matrix** input_labels, int dataset_size)
{
    // Allocate all the memory
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

    Matrix *prediction;
    Matrix *target;

    int last_layer_idx =  network->num_layers - 1;
    Layer *last_layer = network->layers[last_layer_idx];

    int res = 0;

    while (true) {

        for (int i = 0; i < dataset_size; i++)
        {
            prediction = predict(network, input_dataset[i]);
            target = input_labels[i];

            if (predict == NULL)
            {
                log_exception(__func__, "Exception during prediction");
                return -1;
            }

            // Calculate initial delta
            res = 0;
            res += subtract(prediction, target);
            res += apply(last_layer->neurons, NULL, last_layer->activation->fn_der);
            res += hadamard(prediction, last_layer->neurons, deltas[last_layer_idx]);
            if (res < 0)
            {
                log_exception(__func__, "Exception during output delta calculation");
                return res;
            }

            // Update delta weights
            res = 0;
            res += multiply_transposed(deltas[last_layer_idx], network->layers[last_layer_idx - 1]->neurons_act, temp_delta_weights[last_layer_idx]);
            res += add(delta_weights[network->num_layers - 1], temp_delta_weights[last_layer_idx]);
            if (res < 0)
            {
                log_exception(__func__, "Exception during output delta weights calculation");
                return res;
            }

            // Update delta biases
            res = add(delta_bias[network->num_layers - 1], deltas[last_layer_idx]);
            if (res < 0)
            {
                log_exception(__func__, "Exception during output delta bias calculation");
                return res;
            }

            backpropagate(
                network,
                deltas,
                temp_deltas,
                delta_weights,
                temp_delta_weights,
                transposed_weights,
                delta_bias
            );
        }

        // TODO: Adjust weights

        reset(
            network,
            deltas,
            temp_deltas,
            delta_weights,
            temp_delta_weights,
            transposed_weights,
            delta_bias
        );
        
        break;    
    }

    cleanup(
        network->num_layers,
        deltas,
        temp_deltas,
        delta_weights,
        temp_delta_weights,
        transposed_weights,
        delta_bias
    );
}
