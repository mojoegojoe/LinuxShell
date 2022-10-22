#include "cd.h"

int cd(char **args)
{
  if (args[1] == NULL)
  {
    print_line("expected argument to \"cd\"\n\0", "\0", 2);
  }
  else
  {
    if (chdir(args[1]) != 0)
    {
      print_line("invalid argument to \"cd\"\n\0", "\0", 2);
    }
  }
  return 1;
}