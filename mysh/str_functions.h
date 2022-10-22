#ifndef STR_FUNCTIONS_H
#define STR_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "output.h"
/* STRING MANIPULATION */
int str_contains(char *string, int str_len, char *toFind, int f_len);
char *str_tok(char *str, const char *delim);
char *strcpy(char *destination, const char *source);
int str_cpy(char *BUFFER, char *SRC, char *delim);
int strcmp(char *str1, char *str2);
void clear_rest(char **buff, int buff_size, int index);
void clear_buffer(char buff[], int buff_size, int index);
void copy_starting(char **buff, char **buff2, int index);


#endif