#include "redirection.h"

/*
Changes the fd based on the command, and runs the
process handling all io redirection functionality

Working commands:
Input < and output > redirection with overwrites
Output >> redirection with append
Error output 2> redirection

 */
void exec_ioredir(char **arg_buff, char **command_buff, int bckgrnd_flag)
{
    int fd, saved;

    if (strcmp(command_buff[0], ">") == 0 || strcmp(command_buff[0], ">>") == 0)
    {
        saved = dup(1);
        if (strcmp(command_buff[0], ">") == 0)
        {
            fd = open(command_buff[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
        }
        else
        {
            fd = open(command_buff[1], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
        }

        if (fd == -1)
        {
            print_line("File failed to open\n\0", "\0", 2);
            exit_shell(EXIT_FAILURE);
        }
        dup2(fd, 1);
        close(fd);

        runprocess(arg_buff, bckgrnd_flag);

        // restores buffer
        dup2(saved, 1);
        close(saved);
    }
    else if (strcmp(command_buff[0], "<") == 0)
    {
        saved = dup(0);
        fd = open(command_buff[1], O_RDONLY);
        if (fd == -1)
        {
            print_line("File failed to open\n\0", "\0", 2);
            exit_shell(EXIT_FAILURE);
        }

        dup2(fd, 0);
        close(fd);

        runprocess(arg_buff, bckgrnd_flag);
        dup2(saved, 0);
        close(saved);
    }
    else if (strcmp(command_buff[0], "2>") == 0)
    {
        saved = dup(2);
        fd = open(command_buff[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
        if (fd == -1)
        {
            print_line("File failed to open\n\0", "\0", 2);
            exit_shell(EXIT_FAILURE);
        }
        dup2(fd, 2);
        close(fd);

        runprocess(arg_buff, bckgrnd_flag);
        dup2(saved, 2);
        close(saved);
    }

    return;
}
