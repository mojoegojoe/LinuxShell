#ifndef IO_ERROR
#define IO_ERROR
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "constants.h"
int error_line(char BUFFER[], char delim);


#endif