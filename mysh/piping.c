#include "piping.h"

int check_piping(char *command)
{
  unsigned char is_pipe = str_contains(command, BUFF_SIZE, "|", 1);
  if (is_pipe > 0)
    return 1;
  else
    return 0;
}

char **pipe_elements(char *input)
{
  char *p = str_tok(input, "|");
  // char **pipe_args;
  char **pipe_args = malloc(256 * sizeof(char *));

  int oof = 0;

  while (p != NULL)
  {
    pipe_args[oof++] = p;
    p = str_tok(NULL, "|");
    // printf("%s", p);
  }

  return pipe_args;
}
void piping(char *command)
{
  // printf("\n passed command \n%s\n", command);

  int status;
  char **pipe_args = pipe_elements(command);
  // printf("%s\n",pipe_args[0]);
  // printf("%s\n",pipe_args[1]);
  int pipes[2], fd = 0;
  pid_t proc;

  for (int j = 0; pipe_args[j] != NULL; j++)
  {
    // printf("%d\n", j);

    // printf("%s\n",pipe_args);
    pipe(pipes);
    proc = fork();

    if (proc < 0)
      perror("");

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
      exit(2);
    }
  }
}
