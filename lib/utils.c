#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "matrix.h"

void logger(int log_level, const char *function_name, const char *message)
{
    if (log_level >= LOG_LEVEL)
    {
        if (log_level == EXCEPTION)
        {
            RED_COLOR;
        }
        printf("%s: %s\n", function_name, message);
        RESET_COLOR;
    }
}

Dataset* create_dataset(
    int train_size,
    int input_size,
    int output_size,
    int val_size,
    double *train_input_mat[train_size][input_size][1],
    double *train_label_mat[train_size][output_size][1],
    double *val_input_mat[val_size][input_size][1],
    double *val_label_mat[val_size][output_size][1])
{
    Dataset *dataset = (Dataset *) malloc (sizeof (Dataset));
    dataset->train_size = train_size;
    dataset->train_inputs = (Matrix **) malloc (sizeof (Matrix*) *train_size);
    dataset->train_labels = (Matrix **) malloc (sizeof (Matrix*) *train_size);

    dataset->val_size = val_size;
    dataset->val_inputs = (Matrix **) malloc (sizeof (Matrix*) *val_size);
    dataset->val_labels = (Matrix **) malloc (sizeof (Matrix*) *val_size);

    for (int i = 0; i < train_size; i++)
    {
        dataset->train_inputs[i] = create_matrix(input_size, 1, train_input_mat[i]);
        dataset->train_labels[i] = create_matrix(output_size, 1, train_label_mat[i]);
    }

    for (int i = 0; i < val_size; i++)
    {
        dataset->val_inputs[i] = create_matrix(input_size, 1, val_input_mat[i]);
        dataset->val_labels[i] = create_matrix(output_size, 1, val_label_mat[i]);
    }
    
    return dataset;
}

int delete_dataset(Dataset *dataset)
{
    for (int i = 0; i < dataset->train_size; i++)
    {
        delete(dataset->train_inputs[i]);
        delete(dataset->train_labels[i]);
    }

    for (int i = 0; i < dataset->val_size; i++)
    {
        delete(dataset->val_inputs[i]);
        delete(dataset->val_labels[i]);
    }

    free(dataset->train_inputs);
    free(dataset->train_labels);
    free(dataset->val_inputs);
    free(dataset->val_labels);

    free(dataset);
    return 0;
    
    
}