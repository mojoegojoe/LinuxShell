#ifndef SHELL_H
#define SHELL_H
#include "common.h"
void shell();
void execute_command(char *input_buff);
void get_args(char *str, char **arg_buffer, int arg_buffer_size);
int command_handler(char **commands, int commands_size, char **arg_buffer, int arg_buff_size, char **command_buff);

#endif