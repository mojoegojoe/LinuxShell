#include "shell.h"

void shell()
{
  //pwd();
  char input_buff[BUFF_SIZE];
  do
  {
    if (read_input(input_buff, BUFF_SIZE))
    {
      execute_command(input_buff);
      clear_buffer(input_buff, BUFF_SIZE, 0);
    }
  } while (1);
}
int bckgrnd_check(char **arg_buff)
{

  int i = 0;

  while (arg_buff[i] != NULL)
  {
    i++;
  }
  return strcmp(arg_buff[i - 1], "&");
}

void execute_command(char *input_buff)
{
  char input_copy[BUFF_SIZE];
  char *input = strcpy(input_copy, input_buff);
  // printf("copied cmd %s",input_copy);
  //  printf("ptr to cmd %s",input);
  char *commands[] = {"|", "<", ">",">>","2>","&"};
  char *arg_buff[BUFF_SIZE];
  char *command_buff[BUFF_SIZE];

  //pid_t pid;
  //int status;

  int command;
  //int running = 1;
  //int saved;
  int bckgrnd_flag = 0;

  get_args(input_copy, arg_buff, BUFF_SIZE);
  bckgrnd_flag = bckgrnd_check(arg_buff);
  command = command_handler(commands, COMMAND_SIZE, arg_buff, BUFF_SIZE, command_buff);
  if (check_piping(input_buff))
  {
    // printf("\n %s stuff \n", input_buff);
    piping(input_buff);
    // fork_pipes(command);
    return;
  }
  else if(command == 2)
  {
    exec_ioredir(arg_buff, command_buff, bckgrnd_flag);
  }
  else
  {
    runprocess(arg_buff, bckgrnd_flag);
  }
  clear_buffer(input_copy, BUFF_SIZE, 0);
  return;
}

/*
Given an array of char pointers,
Takes the initial input string, tokenizes it with
delimiter (space and newline),and adds a pointer to each token
in the arg_buffer.
 */

void get_args(char *str, char **arg_buffer, int arg_buffer_size)
{

  arg_buffer[0] = str_tok(str, " \n");
  for (int i = 1; i < arg_buffer_size; i++)
  {
    arg_buffer[i] = str_tok(NULL, " \n");
    if (arg_buffer[i] == NULL)
    {
      break;
    }
  }
  return;
}

/*
compares command array with arg_buffer and
returns a number based on the command detected

0 = no commands
1 = pipe
2 = io redir

If a command is detected, the command buffer is also filled and the
arg buffer is modified to remove the command and its arguments

*/
int command_handler(char **commands, int commands_size, char **arg_buffer, int buff_size, char **command_buff)
{

  int status;
  int found = 0;

  for (int i = 0; i < buff_size && found != 1; i++)
  {
    if (arg_buffer[i] == NULL)
    {
      break;
    }
    for (int j = 0; j < commands_size && found != 1; j++)
    {
      // if command matches with arg_buffer
      if (strcmp(commands[j], arg_buffer[i]) == 0)
      {
        copy_starting(arg_buffer, command_buff, i);
        found = 1;
        if (strcmp(commands[j], "&") == 0)
        {
          status = 0;
        }
        if (strcmp(commands[j], "|") == 0)
        {
          status = 1;
        }
        else if (strcmp(commands[j], "<") == 0 || strcmp(commands[j], ">") == 0
		 || strcmp(commands[j], ">>") == 0 || strcmp(commands[j], "2>") == 0)
        {
          status = 2;
        }
        clear_rest(arg_buffer, buff_size, i);
      }
    }
  }
  if (found == 0)
  {
    status = 0;
  }

  return status;
}


int main()
{

  shell();
  return 0;
}
