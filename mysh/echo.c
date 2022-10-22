#include "echo.h"

void echo(char *command)
{
  printf("%s\n",command);
  char *token = command;
  token = str_tok(NULL, " \"\n\t\r");
  while (token != NULL)
  {
    printf("%s",token);
    //print_line(token, "\0", 1);
    token = str_tok(NULL, " \"\n\t\r");
  }
  //print_line("\n\0", "\0", 1);
  return;
}