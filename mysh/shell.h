#ifndef SHELL_H
#define SHELL_H
#include "common.h"
#include "run_proc.h"
#include "piping.h"
#include "pwd.h"
#include "built_in_handler.h"
#include "input.h"
#include "output.h"
void shell();
int bckgrnd_check(char **arg_buff);
void execute_command(char *input_buff);
void get_args(char *str, char **arg_buffer, int arg_buffer_size);
int command_handler(char **commands, int commands_size, char **arg_buffer, int arg_buff_size, char **command_buff);
int main();
#endif