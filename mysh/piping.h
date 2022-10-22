#ifndef PIPING_H
#define PIPING_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
int check_piping(char *command);
char **pipe_elements(char *input);
void piping(char *command);

#endif