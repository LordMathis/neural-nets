#include "layer.h"
#include "matrix.h"

typedef struct 
{
    Layer **layers;
    int num_layers;
} Network;

Network* create_network(int input_size, int num_layers, int layers[], double (*fn)(double));
int delete_network(Network *network);
Matrix* predict(Network *network, Matrix *input);