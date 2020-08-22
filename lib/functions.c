#include <math.h>
#include <stdlib.h>
#include "functions.h"

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