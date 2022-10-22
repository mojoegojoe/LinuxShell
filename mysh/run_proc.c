#include "run_proc.h"

void runprocess(char **arg_buff, int isBackGround)
{
    if (check_for_built_in(arg_buff))
    {
        handle_builtin_functions(arg_buff);
        return;
    }
    pid_t pid = fork();
    int status;
    if (pid < 0)
    {
        print_line("Error spawing process\n\0", "\0", 2);
        // exit_shell(exit_shell_FAILURE);
    }

    else if (pid == 0)
    {
        // setpgid(0, 0);

        pid_t cmd_pid = execve(arg_buff[0], arg_buff, NULL);
        if (cmd_pid < 0)
        {
            print_line("Command not found, try adding \\bin\\ before command name\n\0", "\0", 2);

            exit_shell(EXIT_FAILURE);
        }
    }
    if (isBackGround != 0)
    {
        waitpid(pid, &status, 0);
    }
    // else (
    //   //getpid()
    // )
}
