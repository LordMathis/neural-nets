#ifndef UTILS_H

#define UTILS_H

#include "matrix.h"

#define RED_COLOR printf("\033[0;31m")
#define GREEN_COLOR printf("\033[0;32m")
#define RESET_COLOR printf("\033[0m" )

#define DEBUG 0
#define INFO 1
#define EXCEPTION 2

#ifndef LOG_LEVEL
#define LOG_LEVEL 1
#endif

typedef struct
{
    int train_size;
    Matrix **train_inputs;
    Matrix **train_labels;
    int val_size;
    Matrix **val_inputs;
    Matrix **val_labels;
} Dataset;

Dataset* create_dataset(
    int train_size,
    int input_size,
    int output_size,
    int val_size,
    Matrix **train_inputs,
    Matrix **train_labels,
    Matrix **val_inputs,
    Matrix **val_labels
);
int delete_dataset(Dataset *dataset);

typedef enum {
    loss,
    acc
} Monitor;

void logger(int log_level, const char *function_name, const char *message);

Matrix** load_csv(char *filename, int lines, int line_length);

#endif
