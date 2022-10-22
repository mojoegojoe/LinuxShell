#ifndef IO_WRITELINE
#define IO_WRITELINE
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "constants.h"
int write_line(char BUFFER[], char delim);

#endif