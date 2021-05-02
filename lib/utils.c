#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    for (int i = 0; i < dataset->train_size; i++)
    {
        delete_matrix(dataset->train_inputs[i]);
        delete_matrix(dataset->train_labels[i]);
    }

    for (int i = 0; i < dataset->val_size; i++)
    {
        delete_matrix(dataset->val_inputs[i]);
        delete_matrix(dataset->val_labels[i]);
    }

    free(dataset->train_inputs);
    free(dataset->train_labels);
    free(dataset->val_inputs);
    free(dataset->val_labels);

    free(dataset);
    return 0;    
}

Matrix** load_csv(char *filename, int lines, int line_length)
{
    FILE* fp = fopen(filename, "r");

    if (!fp) 
    {
        logger(EXCEPTION, __func__, "Failed to open csv file");
        return NULL;
    }

    Matrix **result = (Matrix**) malloc (sizeof (Matrix*) * lines);

    int buffer_length = line_length*4;
    char buffer[buffer_length];

    int line_idx = 0;
    while(fgets(buffer, buffer_length, fp)) {        
        char *token = strtok(buffer, ",");
        double mat[line_length][1];

        int i = 0;
        while( token != NULL ) {
            mat[i++][0] = strtod(token, NULL);
            token = strtok(NULL, ",");
        }

        result[line_idx++] = create_matrix(line_length, 1, mat);
    }

    fclose(fp);
    return result;
}

int vectorize(Matrix **a, int length, int num_classes)
{
    for (int i = 0; i < length; i++)
    {
        int index = (int) a[i]->matrix[0][0];
        if (index >= num_classes)
        {
            return -1;
        }

        double mat[num_classes][1];
        for (int j = 0; j < num_classes; j++)
        {
            mat[j][0] = 0;
        }
        
        mat[index][0] = 1;

        delete_matrix(a[i]);
        a[i] = create_matrix(num_classes, 1, mat);
    }

    return 0;    
}

int normalize(Matrix **a, int length, int max_num)
{
    for (int i = 0; i < length; i++)
    {
        Matrix *matrix = a[i];
        if (is_null(matrix))
        {
            return -1;
        }

        for (int j = 0; j < matrix->rows; j++)
        {
            for (int k = 0; k < matrix->cols; k++)
            {
                matrix->matrix[j][k] = matrix->matrix[j][k] / max_num;
            }            
        }        
    }
    
    return 0;
}