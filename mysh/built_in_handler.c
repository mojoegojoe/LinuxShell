#include "built_in_handler.h"


/********************************************************
/    @FUNCION check_for_built_in
/    @input   args - char **
/             
/                      
/    @output  1 if char** args conatins pwd,cd,echo,exit
/           and 0 if input does not contain any of them
/    @method  Check input for built in functions of the 
/           shell
/
********************************************************/
int check_for_built_in(char **args)
{
  if ((strcmp(args[0], "pwd") == 0) || (strcmp(args[0], "cd") == 0) || (strcmp(args[0], "echo") == 0) || (strcmp(args[0], "exit") == 0))
  {
    return 1;
  }
  return 0;
}
/********************************************************
/    @FUNCION handle_builtin_functions
/    @input   args - char **
/             
/                      
/    @output  void 
/    @method  Handles taking user input and routing input
/       to the shells built in function
/
********************************************************/
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