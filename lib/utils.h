#ifndef UTILS_H

#define UTILS_H
#define RED_COLOR printf("\033[0;31m")
#define GREEN_COLOR printf("\033[0;32m")
#define RESET_COLOR printf("\033[0m" )

void log_info(const char *function_name, const char *message);
void log_exception(const char *function_name, const char *message);

#endif
