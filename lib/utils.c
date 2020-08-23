#include <stdio.h>

void log_info(const char *function_name, const char *message)
{
    printf("%s: %s\n", function_name, message);
}