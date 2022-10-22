#ifndef PIPING_H
#define PIPING_H
#include "run_proc.h"
#include "str_functions.h"
#include "shell.h"
int check_piping(char *command);
char **pipe_elements(char *input);
void piping(char *command);

#endif