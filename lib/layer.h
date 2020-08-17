#ifndef LAYER_H
#define LAYER_H

#include "matrix.h"

typedef struct
{
    Matrix *weights;
    Matrix *bias;
    Matrix *neurons;
    double (*activation_fn)(double);
    int num_neurons;
} Layer;

Layer* create_layer(int layer_size, int input_size, double (*fn)(double));
int layer_compute(Layer *layer, Matrix *input);
int delete_layer(Layer *layer);

#endif /* LAYER_H */