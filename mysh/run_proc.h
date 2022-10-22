#ifndef RUN_PROC_H
#define RUN_PROC_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "common.h"
#include "str_functions.h"
#include "built_in_handler.h"
#include "redirection.h"
void runprocess(char **arg_buff, int isBackGround);

#endif 