#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void runprocess(char **arg_buff, int isBackGround);
char *strtok(char *str, const char *delim);
void get_args(char *str, char **arg_buffer, int arg_buffer_size);
int read_input(char *buffer, int buffer_size);
int command_handler(char **commands, int commands_size, char **arg_buffer, int arg_buff_size, char **command_buff);
int strcmp(char *str1, char *str2);
void clear_rest(char **buff, int buff_size, int index);
void clear_buffer(char buff[], int buff_size, int index);
void copy_starting(char **buff, char **buff2, int index);
void exec_ioredir(char **arg_buff, char **command_buff,int bckgrnd_flag);
char **pipe_elements(char *input);
void piping(char *command);
void shell();
void execute_command(char *input_buff);
// int check_redirection(char *command);
int check_piping(char *command);
int bckgrnd_check(char ** arg_buff);


#define BUFF_SIZE 80
#define COMMAND_SIZE 6
#define EXIT_FAILURE 1

// int check_redirection(char *command)
// {
//   char *out = strstr(command, ">");
//   char *in = strstr(command, "<");

//   if ((out != NULL) && (in != NULL))
//     return 3;

//   else if (out != NULL)
//     return 2;

//   else if (in != NULL)
//     return 1;

//   else
//     return 0;
// }

unsigned char strContains(char* string, int str_len, char* toFind, int f_len)
{
    unsigned char slen = str_len;
    unsigned char tFlen = f_len;
    unsigned char found = 0;

    if( slen >= tFlen )
    {
        for(unsigned char s=0, t=0; s<slen; s++)
        {
            do{

                if( string[s] == toFind[t] )
                {
                    if( ++found == tFlen ) return 1;
                    s++;
                    t++;
                }
                else { s -= found; found=0; t=0; }

              }while(found);
        }
        return 0;
    }
    else return -1;
}

int check_piping(char *command)
{
  unsigned char is_pipe = strContains(command,BUFF_SIZE, "|",1);
  if (is_pipe > 0)
    return 1;

  else
    return 0;
}

void shell()
{
  char input_buff[BUFF_SIZE];

  // char ** buff_test = &input_buff;
  do
  {
    // CHILD_ID = -1;
    // prompt();
    input_buff[read_input(input_buff, BUFF_SIZE)-1] = '\0';
    //printf("this is string: %s\n", input_buff);
    
    char **commands;
    // commands = tokenize(input);
    // for(int i = 0; i < no; i++)
    //piping(input_buff);
    execute_command(input_buff);

    clear_buffer(input_buff, BUFF_SIZE, 0);
  } while (1);
}

void execute_command(char *input_buff)
{
  char *commands[] = {"|","<", ">","2>",">>","&"};
  char *arg_buff[BUFF_SIZE];
  char *command_buff[BUFF_SIZE];
  //pid_t pid;
  //int status;
  int command;
  int running = 1;
  int saved;
  int bckgrnd_flag;

  if (check_piping(input_buff))
  {
    piping(input_buff);
    // fork_pipes(command);
    return;
  }

  get_args(input_buff, arg_buff, BUFF_SIZE);
  //  for(int i = 0; i<BUFF_SIZE; i++){
  //  printf("args: %s\n", arg_buff[i]);
  // }
  bckgrnd_flag = bckgrnd_check(arg_buff);
  command = command_handler(commands, COMMAND_SIZE, arg_buff, BUFF_SIZE, command_buff);
  //  for(int i = 0;i<BUFF_SIZE; i++){
  //  printf("command args: %s\n", command_buff[i]);
  // }
  //   for(int i = 0; i<BUFF_SIZE; i++){
  //  printf("args: %s\n", arg_buff[i]);
  // }


 
  // if (check_redirection(command))
  // {
  //   exec_ioredir(arg_buff, command_buff);
  //   return;
  // }

  //printf("\nstatus: %d\n", command);
  
  switch (command)
  {
  case 0:
    runprocess(arg_buff, bckgrnd_flag);
    break;
  case 2:
    exec_ioredir(arg_buff, command_buff,bckgrnd_flag);
    break;
  }
  return;
}

int main()
{

  shell();
  return 0;
}

void runprocess(char **arg_buff, int isBackGround)
{
  pid_t pid = fork();
  int status;
  if (pid < 0)
  {
    perror("Error");
    // exit(EXIT_FAILURE);
  }

  else if (pid == 0)
  {
    // setpgid(0, 0);
    pid_t cmd_pid = execve(arg_buff[0], arg_buff, NULL);
    if (cmd_pid < 0)
    {
      perror("Command not found");
      exit(EXIT_FAILURE);
    }
  }
  
  if (isBackGround != 0)
    {
      printf("waiting\n");
      waitpid(pid, &status, 0);
    }

}

// TO DO: EXECUTE io redirection

void exec_ioredir(char **arg_buff, char **command_buff, int bckgrnd_flag)
{
  int fd,saved;

  if (strcmp(command_buff[0], ">") == 0 || strcmp(command_buff[0], ">>") == 0)
  {
    saved = dup(1);
    if(strcmp(command_buff[0], ">") == 0)
    {
      fd = open(command_buff[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    }
    else
    {
      fd = open(command_buff[1], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
    }
	
    dup2(fd, 1);
    close(fd);
    
    runprocess(arg_buff,bckgrnd_flag);
    
    //restore buffer
    dup2(saved,1);
    close(saved);
  }
  else if (strcmp(command_buff[0], "<") == 0)
  {
    saved = dup(0);
    fd = open(command_buff[1], O_RDONLY);
    dup2(fd, 0);
    close(fd);

    runprocess(arg_buff,bckgrnd_flag);
    dup2(saved,0);
    close(saved);
  }
  else if(strcmp(command_buff[0], "2>") == 0)
  {
    saved = dup(2);
    fd = open(command_buff[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    dup2(fd, 2);
    close(fd);

    runprocess(arg_buff,bckgrnd_flag);
    dup2(saved,2);
    close(saved);
  }

  return;
}

int bckgrnd_check(char ** arg_buff){

  int i = 0;
  
  while(arg_buff[i] != NULL){
    i++;
  }
  return strcmp(arg_buff[i-1], "&");
}

char **pipe_elements(char *input)
{
  char *p = strtok(input, "|");
  // char **pipe_args;
  char **pipe_args = malloc(256 * sizeof(char *));

  int oof = 0;

  while (p != NULL)
  {
    pipe_args[oof++] = p;
    p = strtok(NULL, "|");
    //printf("%s", p);
  }

  return pipe_args;
}
void piping(char *command)
{
  //printf("\n passed command \n%s\n", command);
  
  int status;
  char **pipe_args = pipe_elements(command);
  // printf("%s\n",pipe_args[0]);
  // printf("%s\n",pipe_args[1]);
  int pipes[2], fd = 0;
  pid_t proc;

  for (int j = 0; pipe_args[j] != NULL; j++)
  {
    //printf("%d\n", j);
    
    // printf("%s\n",pipe_args);
    pipe(pipes);
    proc = fork();

    if (proc < 0)
      perror("Nash");

    else if (proc > 0)
    {
      wait(NULL);
      close(pipes[1]);
      fd = pipes[0];
    }

    else if (proc == 0)
    {
      //printf("%s\n", pipe_args[j]);
      
      dup2(fd, 0);

      if (pipe_args[j + 1] != NULL)
        dup2(pipes[1], 1);

      close(pipes[0]);

      // char * arg_buff[BUFF_SIZE];
      // get_args(pipe_args[j], arg_buff, BUFF_SIZE);
      execute_command(pipe_args[j]);
      // int ret = execve(pipe_args[j], pipe_args, NULL);

      // runprocess(arg_buff,0,&status);
      exit(2);
      // get_args(input_buff, arg_buff, BUFF_SIZE);
      // execute_com(pipe_args[j]);
      // exit(2);
    }
  }
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
	if(strcmp(commands[j], "&") == 0){
	  status = 0;
	}
        if (strcmp(commands[j], "|") == 0)
        {
          status = 1;
        }
        else if (strcmp(commands[j], "<") == 0 || strcmp(commands[j], ">") == 0
		 || strcmp(commands[j], "2>") == 0 || strcmp(commands[j], ">>") == 0)
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

/*
set the pointer at index and the pointers that come after
it in buff to NULL
*/
void clear_rest(char **buff, int buff_size, int index)
{
  for (int i = index; i < buff_size; i++)
  {
    buff[i] = NULL;
  }
  return;
}

void clear_buffer(char buff[], int buff_size, int index)
{
  for (int i = index; i < buff_size; i++)
  {
    buff[i] = 0;
  }
  return;
}
/*
copies content of buff into buff2 starting at an index

 */
void copy_starting(char **buff, char **buff2, int index)
{

  for (int i = index; buff[i] != NULL; i++)
  {
    buff2[i - index] = buff[i];
  }
  return;
}
/*
own strcmp function identical to the library
 */
int strcmp(char *str1, char *str2)
{

  while (*str1)
  {
    if (*str1 != *str2)
    {
      break;
    }
    str1++;
    str2++;
  }
  return *(unsigned char *)str1 - *(unsigned char *)str2;
}

/*
TODO:

- seperate execute functions for each type of command
  (pipe command, regular command (identical to the one above), io redirection,
  maybe built in commands?)

- parse to detect pipe, io redirection or ampersand


 */
int read_input(char *buffer, int buffer_size)
{
  int status;

  if (buffer == NULL)
  {
    status = -1;
    return status;
  }
  else
  {
    status = read(0, buffer, buffer_size);
  }
  return status;
}

/*
Given an array of char pointers,
Takes the initial input string, tokenizes it with
delimiter (space and newline),and adds a pointer to each token
in the arg_buffer.
 */

void get_args(char *str, char **arg_buffer, int arg_buffer_size)
{

  arg_buffer[0] = strtok(str, " \n");
  for (int i = 1; i < arg_buffer_size; i++)
  {
    arg_buffer[i] = strtok(NULL, " \n");
    if (arg_buffer[i] == NULL)
    {
      break;
    }
  }
  return;
}
/*
- works the same way as strtok function
 */

char *mystrtok(char *str, const char *delim)
{

  static char *token;

  if (str != NULL)
  {
    token = str;
  }
  else
  {
    str = token;
  }

  if (*token == '\0')
  {
    return NULL;
  }

  while (*token != '\0')
  {

    for (int i = 0; delim[i] != '\0'; i++)
    {

      if (*token == delim[i])
      {
        // any multiple leading delimiters skipped
        if (token == str)
        {
          token++;
          str++;
        }
        else
        {
          *token = '\0';
          token++;
          break;
        }
      }
    }

    if (*token == '\0')
    {
      return str;
    }
    token++;
  }
  return str;
}
