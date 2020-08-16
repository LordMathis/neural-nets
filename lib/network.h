#include "matrix.h"

typedef struct
{
    Matrix *weights;
    Matrix *bias;
    Matrix *neurons;
    double (*activation_fn)(double);
    int num_neurons;
} Layer;

typedef struct 
{
    Layer **layers;
    int num_layers;
} Network;