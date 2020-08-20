#include "test.h"
#include "test_utils.h"

int main()
{
    int res = 0;
    res += test_matrix();
    res += test_layer();
    res += test_network();
    res += test_functions();

    eval_test_result("All tests passed!", res);

    return 0;
}