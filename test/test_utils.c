#include <stdbool.h>
#include <stdio.h>
#include <test_utils.h>

int fail(const char *test_name, const char *message)
{
    printf("%s%s %s%s\n", RED_COLOR, test_name, message, RESET_COLOR);
    return -1;
}

int eval_test_result(const char *test_name, int result)
{
    if (result<0) {
        printf("%s%s failed%s\n", RED_COLOR, test_name, RESET_COLOR);
    } else {
        printf("%s%s passed%s\n", GREEN_COLOR, test_name, RESET_COLOR);
    }

    return result;
}