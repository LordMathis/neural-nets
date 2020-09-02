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
    Matrix **train_inputs,
    Matrix **train_labels,
    Matrix **val_inputs,
    Matrix **val_labels)
{
    Dataset *dataset = (Dataset *) malloc (sizeof (Dataset));
    dataset->train_size = train_size;
    dataset->val_size = val_size;

    if (train_inputs == NULL || train_labels == NULL)
    {
        return NULL;
    }

    dataset->train_inputs = train_inputs;
    dataset->train_labels = train_labels;
    dataset->val_inputs = val_inputs;
    dataset->val_labels = val_labels;

    if (val_inputs == NULL)
    {
        dataset->val_inputs = train_inputs;
        dataset->val_labels = train_labels;
    }

    return dataset;
}

int delete_dataset(Dataset *dataset)
{
    free(dataset);
    return 0;    
}