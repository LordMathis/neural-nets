#include "test.h"
#include "test_utils.h"
#include "../lib/functions.h"

static int test_act_sigmoid()
{
    int res = 0;

    if (act_sigmoid(0) != 0.5)
    {
        res += fail(__func__, "Unexpected sigmoid value ")
    }
}

int test_functions()
{
    int res = 0;
    // res +=
    return res;
}