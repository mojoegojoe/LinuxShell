#include "piping.h"


/********************************************************
/    @FUNCION check_piping
/    @input   command - char *
/             
/                      
/    @output  int - 1 if | is in char * command, else 0
/    @method  Checks in the input command has a pipe
/            character or | symbol. 
/
********************************************************/
int check_piping(char *command)
{
  unsigned char is_pipe = str_contains(command, BUFF_SIZE, "|", 1);
  if (is_pipe > 0)
    return 1;
  else
    return 0;
}

/********************************************************
/    @FUNCION pipe_elements
/    @input   input - char *
/             
/                      
/    @output  char** - returns references to the commands
/            seperated by the pipe
/    @method  Splits the input into parts divided by a pipe
/           symbol
/
********************************************************/
char **pipe_elements(char *input)
{
  char *p = str_tok(input, "|");
  char **pipe_args = malloc(256 * sizeof(char *));

  int oof = 0;

  while (p != NULL)
  {
    pipe_args[oof++] = p;
    p = str_tok(NULL, "|");
  }

  return pipe_args;
}

/********************************************************
/    @FUNCION piping
/    @input   command - char *
/             
/                      
/    @output  void - 
/    @method  Sets up the pipe for the child process 
/            before forking. 
/
********************************************************/
void piping(char *command)
{
  char **pipe_args = pipe_elements(command);
  int pipes[2], fd = 0;
  pid_t proc;

  for (int j = 0; pipe_args[j] != NULL; j++)
  {
    if (pipe(pipes)) {
        proc = fork();

        if (proc < 0)
        print_line("Fork Failed:\n\0", "\0", 2);
    

        else if (proc > 0)
        {
        wait(NULL);
        close(pipes[1]);
        fd = pipes[0];
        }

        else if (proc == 0)
        {

        dup2(fd, 0);

        if (pipe_args[j + 1] != NULL)
            dup2(pipes[1], 1);

        close(pipes[0]);
        execute_command(pipe_args[j]);
        exit_shell(2);
        }
    }
    else {
        print_line("Failed to establish pipe\n\0", "\0", 2);
    }
  }
}
