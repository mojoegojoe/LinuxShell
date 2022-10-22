#include "echo.h"

void echo(char **command)
{
  for (int i = 1; command[i] != NULL; i++) {
    print_line(command[i], "\0", 1);
  }
  print_line("\n\0", "\0", 1);
  return;
}