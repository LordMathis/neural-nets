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

int train(Network *network, Matrix **input_dataset, int dataset_size)
{
    // Set up deltas
    Matrix **delta_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);
    Matrix **delta_bias = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);
    for (int i = 0; i < network->num_layers; i++)
    {
        int rows = network->layers[i]->weights->rows;
        int cols = network->layers[i]->weights->cols;
        delta_weights[i] = create_matrix(rows, cols, NULL);

        rows = network->layers[i]->bias->rows;
        cols = network->layers[i]->bias->cols;
        delta_bias[i] = create_matrix(rows, cols, NULL);
    }


    for (int i = 0; i < dataset_size; i++)
    {
        Matrix *result = predict(network, input_dataset[i]);


    }
    



    // Cleanup
    for (int i = 0; i < network->num_layers; i++)
    {
        delete(delta_weights[i]);
        delete(delta_bias[i]);
    }
    free(delta_weights);
    free(delta_bias);
}