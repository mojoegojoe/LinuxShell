#ifndef IO_REDIRECTION_H
#define  IO_REDIRECTION_H
int check_redirection(char *command);
void exec_ioredir(char **arg_buff, char **command_buff, int bckgrnd_flag);
#endif