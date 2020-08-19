#include <stdbool.h>

#define RED_COLOR = "\033[0;31m"
#define GREEN_COLOR = "\033[0;32m"
#define RESET_COLOR = "\033[0m" 

int fail(const char *test_name, const char *message);
int eval_test_result(const char *test_name, int result);