#include <stdio.h>
#include "utils.h"

void log_info(const char *function_name, const char *message)
{
    printf("%s: %s\n", function_name, message);
}

void log_exception(const char *function_name, const char *message)
{
    RED_COLOR;
    printf("%s: %s\n", function_name, message);
    RESET_COLOR;
}