#include "matrix.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Activation functions

double act_sigmoid(double num);
double act_sigmoid_der(double num);
double act_relu(double num);
double act_relu_der(double num);

typedef enum
{
    SIGMOID,
    RELU
} ActivationType;


typedef struct
{
    double (*fn)(double);
    double (*fn_der)(double);
    ActivationType type;
} Activation;

Activation* create_sigmoid_activation();
Activation* create_relu_activation();

int delete_activation(Activation *activation);

// Cost functions

typedef enum
{
    MEAN_SQUARED_ERROR,
    CROSS_ENTROPY
} CostType;


double cost_mse(Matrix *prediction, Matrix *target);
double cost_cross_entropy(Matrix *prediction, Matrix *target);

#endif /* FUNCTIONS_H */
