#include "matrix.h"
#include "network.h"
#include <stdlib.h>


Layer* create_layer(int layer_size, int input_size, double (*fn)(double))
{
    Layer *layer = (Layer *) malloc (sizeof (Layer));

    layer->num_neurons = layer_size;
    layer->activation_fn = fn;

    layer->weights = create_matrix(input_size, layer_size, NULL);
    layer->bias = create_matrix(layer_size, 1, NULL);
    layer->neurons = create_matrix(layer_size, 1, NULL);

    init_layer(layer);

    return layer;
}

static int init_layer(Layer *layer)
{
    Matrix *weights = layer->weights;
    Matrix *bias = layer->bias;

    srand(time(NULL));
    int range = sqrt(6/(weights->rows + weights->cols));

    for (int i = 0; i < weights->rows; i++)
    {
        for (int j = 0; j < weights->cols; j++)
        {
            weights->matrix[i][j] = (double)rand()/RAND_MAX*2*range - range;
        }        
    }

    for (int i = 0; i < bias->rows; i++)
    {
        bias->matrix[i][1] = (double)rand()/RAND_MAX;
    }
    
    return 0;  
}

int layer_compute(Layer *layer, Matrix *input)
{
    multiply(layer->weights, input, layer->neurons);
    add(layer->neurons, layer->bias);
    apply(layer->neurons, layer->activation_fn);
}

int delete_layer(Layer *layer)
{
    if (layer == NULL) {
        return -1;
    }
    
    delete(layer->weights);
    delete(layer->bias);
    delete(layer->neurons);

    free(layer);
    layer = NULL;
    return 0;
}

Network* create_network(int input_size, int num_layers, int layers[], double (*fn)(double))
{
    Network *network = (Network *) malloc (sizeof (Network));
    network->num_layers = num_layers;

    network->layers = (Layer **) malloc (sizeof (Layer*) *num_layers);
    int prev_layer_size = input_size;
    for (int i = 0; i < num_layers; i++)
    {
        network->layers[i] = create_layer(layers[i], prev_layer_size, fn);
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
        layer_input = layer->neurons;
    }
    
    return layer_input;
}