#include "init.h"
int init_shell()
{

    char input_buff[BUFF_SIZE];
    char *arg_buff[BUFF_SIZE];
    pid_t pid;
    int status;
    int running = 1;

    // test main shell loop
    while (running)
    {

        // replace printf with our write function
        printf("$ ");

        // replace fgets with our input function
        if (fgets(input_buff, BUFF_SIZE, stdin) != NULL)
        {
            pid = fork();
            if (pid == 0)
            {
                get_args(input_buff, arg_buff);
                execve(arg_buff[0], arg_buff, NULL);
            }
            waitpid(pid, &status, 0);
        }
    }
    return 0;
    // print greeting screen
    // getenv username and password
}
