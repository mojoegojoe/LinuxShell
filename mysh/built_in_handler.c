#include "built_in_handler.h"

int check_for_built_in(char **args)
{
  if ((strcmp(args[0], "pwd") == 0) || (strcmp(args[0], "cd") == 0) || (strcmp(args[0], "echo") == 0) || (strcmp(args[0], "exit") == 0))
  {
      //printf("\n%s\n\n\n\n",args[0]);
    return 1;
  }
  return 0;
}
void handle_builtin_functions(char **input)
{
  char *command = str_tok(input[0], " \n\t\r");
//   printf("\n%s\n",command);
  if (strcmp(command, "pwd") == 0) {
    pwd();
  }
  else if (strcmp(command, "cd") == 0) {
    // printf("%s\n",input[1]);
    cd(input);

  } else if (strcmp(command, "echo") == 0) {
    // printf("%s\n",input[1]);
    // for (int i = 0; input[i+1] != NULL; i++) {
    //   printf("%s",input[i+1]);
    // }
    echo(input);
  } else if (strcmp(command, "exit") == 0) {
    // printf("%s\n",input[1]);
    // for (int i = 0; input[i+1] != NULL; i++) {
    //   printf("%s",input[i+1]);
    // }
    exit_shell(EXIT_SUCCESS);
  }
}