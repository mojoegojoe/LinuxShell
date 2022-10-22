#include "run_proc.h"


/********************************************************
/    @FUNCION runprocess
/    @input   arg_buff - char **
/             isBackGround - int
/             
/                      
/    @output  void 
/    @method  Handles the execution of provided command, 
/           and allows for background execution. If 
/           isBackGround is 1, the process will wait for 
/           for the child to finish. Otherwise it will 
/           run in the background.
/
********************************************************/
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
    }

    else if (pid == 0)
    {
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
}
