#include "echo.h"

/********************************************************
/    @FUNCION echo
/    @input   BUFFER - Pointer to a defined char array
/             
/                       function set by delim[0]
/    @output  void  - 
/    @method  Takes input from stdin and sends it to 
/       stdout, the current implementation has issue 
/       with removing spaces,tabs, and newlines from the
/       input.
/
********************************************************/
void echo(char **command)
{
  for (int i = 1; command[i] != NULL; i++) {
    print_line(command[i], "\0", 1);
  }
  print_line("\n\0", "\0", 1);
  return;
}
