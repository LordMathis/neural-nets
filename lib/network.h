#include "layer.h"
#include "matrix.h"
#include "functions.h"
#include "utils.h"

typedef struct 
{
    Layer **layers;
    int num_layers;
} Network;

Network* create_network(int input_size, int num_layers, int layers[], Activation *activation);
void print_network(Network *network);
int delete_network(Network *network);
Matrix* predict(Network *network, Matrix *input);
double accuracy(Network *network, Matrix **inputs, Matrix **targets, int input_length);
int train(Network *network, Dataset *dataset, Monitor *monitor, TrainingOptions *TrainingOptions);
