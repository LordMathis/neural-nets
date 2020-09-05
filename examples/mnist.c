#include "../lib/utils.h"
#include "../lib/functions.h"
#include "../lib/network.h"
#include "../lib/matrix.h"
#include <stdio.h>

int main()
{
    char *train_inputs_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_train_vectors.csv";
    Matrix **train_inputs = load_csv(train_inputs_fn, 60000, 28*28);
    normalize(train_inputs, 60000, 255);

    char *train_labels_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_train_labels.csv";
    Matrix **train_labels = load_csv(train_labels_fn, 60000, 1);
    vectorize(train_labels, 60000, 10);
 
    char *test_inputs_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_test_vectors.csv";
    Matrix **test_inputs = load_csv(test_inputs_fn, 10000, 28*28);
    normalize(test_inputs, 10000, 255);

    char *test_labels_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_test_labels.csv";
    Matrix **test_labels = load_csv(test_labels_fn, 10000, 1);
    vectorize(test_labels, 10000, 10);

    Dataset *dataset = create_dataset(60000, 28*28, 10, 10000, train_inputs, train_labels, test_inputs, test_labels);
    Monitor monitor[] = {acc, loss};

    int layers[] = {50,10};

    Activation *act_sigmoid = create_sigmoid_activation();
    Network *mnist_network = create_network(28*28, 2, layers, act_sigmoid);

    train(mnist_network, dataset, monitor, 100, 10, 2);
}