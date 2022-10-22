#ifndef IO_READLINE
#define IO_READLINE
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "constants.h"

char read_line(char BUFFER[], char delim[]);
int write_line(char BUFFER[], char delim);

#endif