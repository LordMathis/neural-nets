#include "../lib/utils.h"
#include "../lib/functions.h"
#include "../lib/network.h"
#include "../lib/matrix.h"
#include <stdio.h>

int main()
{
    int num_train = 60000;
    int num_test = 10000;

    char *train_inputs_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_train_vectors.csv";
    Matrix **train_inputs = load_csv(train_inputs_fn, num_train, 28*28);
    normalize(train_inputs, num_train, 255);
    logger(INFO, __func__, "Created training dataset");

    char *train_labels_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_train_labels.csv";
    Matrix **train_labels = load_csv(train_labels_fn, num_train, 1);
    vectorize(train_labels, num_train, 10);
    logger(INFO, __func__, "Created training labels dataset");
 
    char *test_inputs_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_test_vectors.csv";
    Matrix **test_inputs = load_csv(test_inputs_fn, num_test, 28*28);
    normalize(test_inputs, num_test, 255);
    logger(INFO, __func__, "Created test dataset");

    char *test_labels_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_test_labels.csv";
    Matrix **test_labels = load_csv(test_labels_fn, num_test, 1);
    vectorize(test_labels, num_test, 10);
    logger(INFO, __func__, "Created test lables dataset");


    Dataset *dataset = create_dataset(num_train, 28*28, 10, num_test, train_inputs, train_labels, test_inputs, test_labels);
    Monitor monitor[] = {acc, loss};

    int layers[] = {30,10};

    Activation *act_sigmoid = create_sigmoid_activation();
    CostType cost_type = CROSS_ENTROPY;
    Network *mnist_network = create_network(28*28, 2, layers, act_sigmoid);

    train(mnist_network, dataset, monitor, cost_type, 10, 30, 2, 0.9);

    delete_network(mnist_network);
    delete_dataset(dataset);
    delete_activation(act_sigmoid);
}