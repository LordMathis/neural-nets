#include <stdbool.h>
#include "../lib/matrix.h"

#define RED_COLOR printf("\033[0;31m")
#define GREEN_COLOR printf("\033[0;32m")
#define RESET_COLOR printf("\033[0m" )

int fail(const char *test_name, const char *message);
int eval_test_result(const char *test_name, int result);
bool is_non_zero(Matrix *matrix);