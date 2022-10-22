#include "redirection.h"

int check_redirection(char *command)
{
    int out = str_contains(command, BUFF_SIZE, ">", 1);
    int in = str_contains(command, BUFF_SIZE, "<", 1);
    int append = str_contains(command, BUFF_SIZE, ">>", 2);

    if ((out > 0) && (in > 0))
        return 3;

    else if ((out > 0) || (append > 0))
        return 2;

    else if (in > 0)
        return 1;

    else
        return 0;
}
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