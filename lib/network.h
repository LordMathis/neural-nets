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
int train(Network *network, Dataset *dataset, Monitor *monitor, int batch_size, int epochs, double learning_rate);

#ifdef UNIT_TEST
#define unit_static

int init_training(
    Network *network,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias
);

int backpropagate(
    Network *network,
    Matrix *input,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias
);

void cleanup(
    int network_length,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias
);

int reset(
    Network *network,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias
);

#else
#define unit_static static
#endif