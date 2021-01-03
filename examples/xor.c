#include "../lib/network.h"
#include "../lib/functions.h"
#include "../lib/utils.h"
#include "../lib/matrix.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    int layers[] = {2,1};

    Activation *act_sigmoid = create_sigmoid_activation();
    Network *xor_network = create_network(2, 2, layers, act_sigmoid);

    Matrix **inputs = (Matrix**) malloc (sizeof (Matrix*) * 4);
    double inputs_mat[4][2][1] = {
        {{1}, {1}},
        {{1}, {0}},
        {{0}, {1}},
        {{0}, {0}}
    };

    Matrix **labels = (Matrix**) malloc (sizeof (Matrix*) * 4);
    double labels_mat[4][1][1] = {
        {{0}},
        {{1}},
        {{1}},
        {{0}}
    };

    for (int i = 0; i < 4; i++)
    {
        inputs[i] = create_matrix(2, 1, inputs_mat[i]);
        labels[i] = create_matrix(1, 1, labels_mat[i]);
    }

    Monitor monitor[] = {acc, loss};
    Dataset *dataset = create_dataset(4,2,1,4, inputs, labels, NULL, NULL);

    CostType cost_type = CROSS_ENTROPY;

    train(xor_network, dataset, monitor, cost_type, 0, 2000, 1);
}