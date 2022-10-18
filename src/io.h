#ifndef IO_H
#define IO_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "constants.h"

char read_line(char BUFFER[], char delim[]);
int print_line(char BUFFER[], char delim[]);
int error_line(char BUFFER[], char delim[]);
int buff_cmp(char BUFFER1[], char BUFFER2[], char delim[]);
int str_cpy(char BUFFER[], char SRC[], char delim[]);

#endif