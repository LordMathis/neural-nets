#include <math.h>
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
