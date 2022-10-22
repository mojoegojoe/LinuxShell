#include "cd.h"


/********************************************************
/    @FUNCION cd
/    @input   args - Pointer to a defined char array
/             
/                      
/    @output  int  - 1 if successfully changed working 
/             directory and 0 if it was unsuccessful
/    @method  Changes the processes current working 
/             directory.
/
********************************************************/
int cd(char **args)
{
  if (args[1] == NULL)
  {
    print_line("expected argument to \"cd\"\n\0", "\0", 2);
    return 0;
  }
  else
  {
    if (chdir(args[1]) != 0)
    {
      print_line("invalid argument to \"cd\"\n\0", "\0", 2);
      return 0;
    }
  }
  return 1;
}