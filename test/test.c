#include "test.h"
#include "test_utils.h"

int main()
{
    int res = 0;
    res += test_matrix();
    res += test_layer();

    if (res<0)
    {
        char *message = 
        fail(__func__, "Tests failed!");
    } else {
        eval_test_result("All tests passed!");
    }

    return 0;
}