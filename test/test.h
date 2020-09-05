#include <stdbool.h>
#include "../lib/matrix.h"

int fail(const char *test_name, const char *message);
int eval_test_result(const char *test_name, int result);
bool is_non_zero(Matrix *matrix);

int test_matrix();
int test_layer();
int test_network();
int test_functions();
