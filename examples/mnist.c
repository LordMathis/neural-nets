#include "../lib/utils.h"

int main()
{
    char *filename = "/home/matus/Projects/personal/matlib/resources/mnist_train_vectors.csv";
    load_csv(filename, 10000, 28*28);
}