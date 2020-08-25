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

static int backpropagate(
    Network *network,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias
);

static void cleanup(
    int network_length,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias
);

static int reset(
    Network *network,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias
);

static int init_training(
    Network *network,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias
);
