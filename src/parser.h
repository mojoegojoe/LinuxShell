#ifndef IO_PARSER
#define IO_PARSER

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "constants.h"


char *str_parser(char *str, const char *delim);
void get_args(char * str, char **arg_buffer);

#endif