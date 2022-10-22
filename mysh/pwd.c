#include "pwd.h"
/*
  @function pwd (print currnt dir)
  @method   if the current working dir is available
               print to user else flag err.	       
  @input    N/A
  @output   N/A
 */
void pwd()
{
  char PWD[BUFF_SIZE];
  if (getcwd(PWD, BUFF_SIZE) == NULL)
  {
    print_line("getcwd() error\0", "\0", 2);
    exit_shell(EXIT_FAILURE);
  }

  else
  {
    print_line(PWD, "\0", 1);
    print_line("\n\0", "\0", 1);
  }
  return;
}
