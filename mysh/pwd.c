#include "pwd.h"

/*Output the processes current parent work directory as an absolute path*/
void pwd()
{
  char PWD[BUFF_SIZE];
  if (getcwd(PWD, BUFF_SIZE) == NULL)
  {
    print_line("getcwd() error\0", "\0", 2);
    exit_shell(EXIT_FAILURE);
    //exit_shell(1);
  }

  else
  {
    print_line(PWD, "\0", 1);
    print_line("\n\0", "\0", 1);
  }
  return;
}
