#include "pwd.h"
void pwd()
{
  char PWD[BUFF_SIZE];
  if (getcwd(PWD, BUFF_SIZE) == NULL)
  {
    print_line("getcwd() error\0", "\0", 2);
    perror("getcwd() error");
    exit_shell(EXIT_FAILURE);
    //exit_shell(1);
  }

  else
  {
    //printf("%s\n",PWD);
    print_line(PWD, "\n", 1);
    print_line("\n\0", "\0", 1);
  }
  return;
}
