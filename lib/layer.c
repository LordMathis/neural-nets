#include "layer.h"
#include "matrix.h"
#include "functions.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

static int init_layer(Layer *layer);

Layer* create_layer(int layer_size, int input_size, Activation *activation)
{
    Layer *layer = (Layer *) malloc (sizeof (Layer));

    layer->num_neurons = layer_size;
    layer->activation = activation;

    layer->weights = create_matrix(layer_size, input_size, NULL);
    layer->bias = create_matrix(layer_size, 1, NULL);
    layer->neurons = create_matrix(layer_size, 1, NULL);
    layer->neurons_act = create_matrix(layer_size, 1, NULL);

    init_layer(layer);

    return layer;
}

static int init_layer(Layer *layer)
{
    Matrix *weights = layer->weights;
    Matrix *bias = layer->bias;

    srand(time(NULL));
    double range = sqrt((double) 6/(weights->rows + weights->cols));

    for (int i = 0; i < weights->rows; i++)
    {
        for (int j = 0; j < weights->cols; j++)
        {
            weights->matrix[i][j] = (double) rand()/RAND_MAX*2*range - range;
        }        
    }

    for (int i = 0; i < bias->rows; i++)
    {
        bias->matrix[i][0] = (double) rand()/RAND_MAX;
    }

    return 0;
}

int layer_compute(Layer *layer, Matrix *input)
{
    multiply(layer->weights, input, layer->neurons);
    add(layer->neurons, layer->bias);
    apply(layer->neurons, layer->neurons_act, layer->activation->fn);

    return 0;
}

int delete_layer(Layer *layer)
{
    if (layer == NULL) {
        return -1;
    }
    
    delete_matrix(layer->weights);
    delete_matrix(layer->bias);
    delete_matrix(layer->neurons);
    delete_matrix(layer->neurons_act);

    free(layer);
    layer = NULL;
    return 0;
}