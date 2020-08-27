#include <stdio.h>
#include "utils.h"

void logger(int log_level, const char *function_name, const char *message)
{
    if (log_level >= LOG_LEVEL)
    {
        if (log_level == EXCEPTION)
        {
            RED_COLOR;
        }
        printf("%s: %s\n", function_name, message);
        RESET_COLOR;
    }
}