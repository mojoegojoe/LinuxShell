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
void runprocess(char **arg_buff, int isBackGround);

#endif 