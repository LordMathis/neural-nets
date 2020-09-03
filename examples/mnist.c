#include "../lib/utils.h"

int main()
{
    char *train_inputs_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_train_vectors.csv";
    Matrix **train_inputs = load_csv(train_inputs_fn, 60000, 28*28);

    char *train_labels_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_train_labels.csv";
    Matrix **train_labels = load_csv(train_labels_fn, 60000, 1);
 
    char *test_inputs_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_test_vectors.csv";
    Matrix **test_inputs = load_csv(test_inputs_fn, 10000, 28*28);

    char *test_labels_fn = "/home/matus/Projects/C/neural-nets/resources/mnist_test_vectors.csv";
    Matrix **test_labels = load_csv(test_labels_fn, 1, 28*28);

    Dataset *dataset = create_dataset(60000, 28*28, 10, 10000, train_inputs, train_labels, test_inputs, test_labels);  
}