#include "built_in_handler.h"

int check_for_built_in(char **args)
{
  if ((strcmp(args[0], "pwd") == 0) || (strcmp(args[0], "cd") == 0) || (strcmp(args[0], "echo") == 0) || (strcmp(args[0], "exit") == 0))
  {
    return 1;
  }
  return 0;
}
void handle_builtin_functions(char **input)
{
  char *command = str_tok(input[0], " \n\t\r");
  if (strcmp(command, "pwd") == 0) {
    pwd();
  }
  else if (strcmp(command, "cd") == 0) {
    cd(input);

  } else if (strcmp(command, "echo") == 0) {
    echo(input);
  } else if (strcmp(command, "exit") == 0) {
    exit_shell(EXIT_SUCCESS);
  }
}