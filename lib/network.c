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
    // Allocate all the memory
    Matrix **delta_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);
    Matrix **temp_delta_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **delta_bias = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);
    Matrix **temp_delta_bias = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **deltas = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **temp_deltas = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers -1);
    Matrix **transposed_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers - 1);

    for (int i = 0; i < network->num_layers; i++)
    {
        int rows = network->layers[i]->weights->rows;
        int cols = network->layers[i]->weights->cols;

        delta_weights[i] = create_matrix(rows, cols, NULL);
        temp_delta_weights[i] = create_matrix(rows, cols, NULL);

        if (i>0)
        {
            transposed_weights[i-1] = create_matrix(cols, rows, NULL);
        }

        int bias_rows = network->layers[i]->bias->rows;
        int bias_cols = network->layers[i]->bias->cols;

        delta_bias[i] = create_matrix(bias_rows, bias_cols, NULL);
        temp_delta_bias[i] = create_matrix(bias_rows, bias_cols, NULL);

        deltas[i] = create_matrix(bias_rows, bias_cols, NULL);

        if (i>0)
        {
            temp_deltas[i-1] = create_matrix(cols, bias_cols, NULL);
        }
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

        Layer *layer;
        Layer *prev_layer;
        for (int i = network->num_layers - 2; i >= 0; i--)
        {
            layer = network->layers[i];
            prev_layer = network->layers[i+1];

            // Compute new delta
            transpose(prev_layer->weights, transposed_weights[i]);
            apply(layer->neurons, NULL, layer->activation->fn_der);
            multiply(transposed_weights[i], deltas[i+1], temp_deltas[i]);
            hadamard(temp_deltas[i], layer->neurons, deltas[i+1]);

            // Compute delta weights
            multiply(deltas[i+1], layer->neurons_act, temp_delta_weights[i]);
            add(delta_weights[i], temp_delta_weights[i]);

            // Compute delta bias
            add(delta_bias[i], deltas[i+1]);
        }      
    }
    

    // Cleanup
    for (int i = 0; i < network->num_layers; i++)
    {
        delete(delta_weights[i]);
        delete(delta_bias[i]);
        delete(temp_delta_weights[i]);
        delete(temp_delta_bias[i]);
        delete(transposed_weights[i]);
        delete(deltas[i]);
    }
    free(delta_weights);
    free(delta_bias);
    free(temp_delta_weights);
    free(temp_delta_bias);
    free(transposed_weights);
    free(deltas);
}