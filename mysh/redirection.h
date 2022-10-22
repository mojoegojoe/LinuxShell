#ifndef IO_REDIRECTION_H
#define  IO_REDIRECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "common.h"
int check_redirection(char *command);
void exec_ioredir(char **arg_buff, char **command_buff, int bckgrnd_flag);
#endif