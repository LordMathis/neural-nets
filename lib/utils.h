#ifndef UTILS_H

#define UTILS_H

#define RED_COLOR printf("\033[0;31m")
#define GREEN_COLOR printf("\033[0;32m")
#define RESET_COLOR printf("\033[0m" )

#define DEBUG 0
#define INFO 1
#define EXCEPTION 2

#ifndef LOG_LEVEL
#define LOG_LEVEL 1
#endif

void logger(int log_level, const char *function_name, const char *message);

#endif
