#include "matrix.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

double act_sigmoid(double num);
double act_sigmoid_der(double num);
double act_relu(double num);
double act_relu_der(double num);

typedef struct
{
    double (*fn)(double);
    double (*fn_der)(double);
} Activation;

Activation* create_sigmoid_activation();
Activation* create_relu_activation();

int delete_activation(Activation *activation);

double mean_squared_error(Matrix *prediction, Matrix *target);

#endif /* FUNCTIONS_H */
