#ifndef LAYER_H
#define LAYER_H

#include "matrix.h"
#include "functions.h"

typedef struct
{
    Matrix *weights;
    Matrix *bias;
    Matrix *neurons;
    Matrix *neurons_act;
    Activation *activation;
    int num_neurons;
} Layer;

Layer* create_layer(int layer_size, int input_size, Activation *activation);
int layer_compute(Layer *layer, Matrix *input);
int delete_layer(Layer *layer);

#endif /* LAYER_H */