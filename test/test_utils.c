#include <stdbool.h>
#include <stdio.h>

int log_failure(const char *test_name, const char *message)
{
    printf("\033[0;31m");    
    printf("%s %s\n", test_name, message);
    printf("\033[0m");

    return -1;
}

int log_success(const char *test_name)
{
    printf("\033[0;32m");    
    printf("%s\n", test_name);
    printf("\033[0m");

    return 0;
}