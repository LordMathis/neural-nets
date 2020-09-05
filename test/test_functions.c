#include "test.h"
#include "../lib/functions.h"
#include <stdbool.h>

static bool is_approx_equal(double a, double b)
{
    int a_int = (int) a * 1000000;
    int b_int = (int) a * 1000000;

    return a_int == b_int;
}


static int test_act_sigmoid()
{
    int res = 0;

    if (act_sigmoid(0) != 0.5 ||
        !is_approx_equal(act_sigmoid(-1), 0.2689414213699951207488) ||
        !is_approx_equal(act_sigmoid(1), 0.7310585786300048792512))
    {
        res += fail(__func__, "Unexpected sigmoid value");
    }

    return eval_test_result(__func__, res);
}

static int test_act_sigmoid_der()
{
    int res = 0;

    if (act_sigmoid_der(0) != 0.25 ||
        !is_approx_equal(act_sigmoid_der(-1), 0.1966119332414818525374) ||
        !is_approx_equal(act_sigmoid_der(1), 0.1966119332414818525374))
    {
        res += fail(__func__, "Unexpected sigmoid derivation value");
    }

    return eval_test_result(__func__, res);
}

static int test_act_relu()
{
    int res = 0;

    if (act_relu(-1) != 0 || act_relu(0) != 0 || act_relu(1) != 1 || act_relu(2) != 2)
    {
        res += fail(__func__, "Unexpected relu value");
    }
    return eval_test_result(__func__, res);
}

static int test_act_relu_der()
{
    int res = 0;

    if (act_relu_der(-1) != 0 || act_relu_der(0) != 0 || act_relu_der(1) != 1 || act_relu_der(2) != 1)
    {
        res += fail(__func__, "Unexpected relu derivation value");
    }
    return eval_test_result(__func__, res);
}

int test_functions()
{
    int res = 0;
    res += test_act_sigmoid();
    res += test_act_sigmoid_der();
    res += test_act_relu();
    res += test_act_relu_der();
    return res;
}