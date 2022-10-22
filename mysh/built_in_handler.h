#ifndef BUILT_IN_HANDLER_H
#define BUILT_IN_HANDLER_H
// #include <stdio.h>
#include "common.h"
#include "str_functions.h"
#include "pwd.h"
#include "cd.h"
#include "echo.h"

int check_for_built_in(char **args);
void handle_builtin_functions(char **input);

#endif