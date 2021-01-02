#include <math.h>
#include <stdlib.h>
#include "functions.h"
#include "matrix.h"

// Activations and derivatives

double act_sigmoid(double num)
{
    return 1 / (1 + exp(-1*num));
}

double act_sigmoid_der(double num)
{
    return exp(-1*num)/pow(1 + exp(-1*num),2);
}

double act_relu(double num)
{
    return fmax(0, num);
}

double act_relu_der(double num)
{
    return num > 0 ? 1 : 0;
}

Activation* create_sigmoid_activation()
{
    Activation *activation = (Activation *) malloc ( sizeof (Activation));
    activation->fn = &act_sigmoid;
    activation->fn_der = &act_sigmoid_der;
}

Activation* create_relu_activation()
{
    Activation *activation = (Activation *) malloc ( sizeof (Activation));
    activation->fn = &act_relu;
    activation->fn_der = &act_relu_der;
}

int delete_activation(Activation *activation)
{
    free(activation);
    activation = NULL;

    return 0;
}

// Cost and derivatives

double cost_mse(Matrix *prediction, Matrix *target)
{
    if (prediction->cols != 1 || target->cols != 1 || prediction->rows != target->rows)
    {
        return -1;
    }

    double loss = 0;
    for (int i = 0; i < prediction->rows; i++)
    {
        loss += pow(prediction->matrix[i][0] - target->matrix[i][0], 2);
    }

    return loss / (2*prediction->rows);    
}

int cost_mse_der(Matrix *prediction, Matrix *target)
{
    return subtract(prediction, target);
}

Cost* create_mse_cost()
{
    Cost *cost = (Cost*) malloc ( sizeof (Cost));
    cost->cost = &cost_mse;
    cost->cost_der = &cost_mse_der;
}
