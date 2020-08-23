#include "layer.h"
#include "matrix.h"
#include "functions.h"

typedef struct 
{
    Layer **layers;
    int num_layers;
} Network;

Network* create_network(int input_size, int num_layers, int layers[], Activation *activation);
int delete_network(Network *network);
Matrix* predict(Network *network, Matrix *input);
int train(Network *network, Matrix **input_dataset, Matrix** input_labels, int dataset_size);