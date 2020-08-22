#include "layer.h"
#include "matrix.h"
#include "network.h"
#include <stdlib.h>


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
        layer_compute(layer, layer_input);
        layer_input = layer->neurons_act;
    }
    
    return layer_input;
}

int train(Network *network, Matrix **input_dataset, Matrix** input_labels, int dataset_size)
{
    // Set up deltas and temp deltas
    Matrix **delta_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);
    Matrix **temp_delta_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **delta_bias = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);
    Matrix **temp_delta_bias = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **deltas = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    for (int i = 0; i < network->num_layers; i++)
    {
        int rows = network->layers[i]->weights->rows;
        int cols = network->layers[i]->weights->cols;

        delta_weights[i] = create_matrix(rows, cols, NULL);
        temp_delta_weights[i] = create_matrix(rows, cols, NULL);

        rows = network->layers[i]->bias->rows;
        cols = network->layers[i]->bias->cols;

        delta_bias[i] = create_matrix(rows, cols, NULL);
        temp_delta_bias[i] = create_matrix(rows, cols, NULL);

        deltas[i] = create_matrix(rows, cols, NULL);
    }

    Matrix *prediction;
    Matrix *target;

    int last_layer_idx =  network->num_layers - 1;
    Layer *last_layer = network->layers[last_layer_idx];

    for (int i = 0; i < dataset_size; i++)
    {
        prediction = predict(network, input_dataset[i]);
        target = input_labels[i];

        // Calculate delta
        subtract(prediction, target);
        apply(last_layer->neurons, NULL, last_layer->activation->fn_der);
        hadamard(prediction, last_layer->neurons, deltas[last_layer_idx]);

        // Update delta weights
        multiply(deltas[last_layer_idx], last_layer->neurons_act, temp_delta_weights[last_layer_idx]);
        add(delta_weights[network->num_layers - 1], temp_delta_weights[last_layer_idx]);

        // Update delta biases
        add(delta_bias[network->num_layers - 1], deltas[last_layer_idx]);
    }
    

    // Cleanup
    for (int i = 0; i < network->num_layers; i++)
    {
        delete(delta_weights[i]);
        delete(delta_bias[i]);
        delete(temp_delta_weights[i]);
        delete(temp_delta_bias[i]);
        delete(deltas);
    }
    free(delta_weights);
    free(delta_bias);
    free(temp_delta_weights);
    free(temp_delta_bias);
    free(deltas);
}