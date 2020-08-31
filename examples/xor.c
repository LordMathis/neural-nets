#include "../lib/network.h"
#include "../lib/functions.h"
#include "../lib/utils.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    int layers[] = {2,1};

    Activation *act_sigmoid = create_sigmoid_activation();
    Network *xor_network = create_network(2, 2, layers, act_sigmoid);

    double inputs_mat[4][2][1] = {
        {{1}, {1}},
        {{1}, {0}},
        {{0}, {1}},
        {{0}, {0}}
    };
    double labels_mat[4][1][1] = {
        {{0}},
        {{1}},
        {{1}},
        {{0}}
    };

    Dataset *dataset = create_dataset(4,2,1,4,inputs_mat, labels_mat, inputs_mat, labels_mat);

    train(xor_network, dataset, 0, 5000, 1);
}