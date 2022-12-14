#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

char *strtok(char *str, const char *delim);
void get_args(char * str, char **arg_buffer,int arg_buffer_size);
int read_input(char* buffer,int buffer_size);
int command_handler(char **commands,int commands_size, char **arg_buffer, int arg_buff_size, char ** command_buff);
int strcmp(char *str1, char *str2);
int bckgrnd_check(char ** arg_buff);
void clear_rest(char ** buff, int buff_size, int index);
void copy_starting(char **buff, char **buff2, int index);
void exec_ioredir(char ** arg_buff, char ** command_buff);


#define  BUFF_SIZE 30
#define  COMMAND_SIZE 3

int main(){

  char *commands [] = {"|","<",">"};
  char input_buff[BUFF_SIZE];
  char *arg_buff[BUFF_SIZE];
  char *command_buff[BUFF_SIZE];
  pid_t pid;
  int status;
  int command;
  int bckgrnd_flag;
  int running = 1;
  
  //test main shell loop
  while(running){

    //replace printf with our write function
    //    printf("$ ");
    
    input_buff[read_input(input_buff,BUFF_SIZE)-1] = '\0';
    //testing printf("input string : %s\n", input_buff);
    get_args(input_buff,arg_buff,BUFF_SIZE);

    /* testing 
    for(int i = 0; arg_buff[i] != NULL; i++){
      printf("this is %s\n", arg_buff[i]);

    }
    */
    
    bckgrnd_flag = bckgrnd_check(arg_buff);
    command = command_handler(commands, COMMAND_SIZE, arg_buff, BUFF_SIZE,command_buff);
    /* testing
    for(int i = 0; command_buff[i] != NULL; i++){
      printf("this is command %s\n", command_buff[i]);

    }
    */
      
    pid = fork();
    if(pid == 0){
      if(command == 2){
	exec_ioredir(arg_buff, command_buff);  
      }
      execve(arg_buff[0],arg_buff,NULL);
    }
    //if command(&) is given to run in background, dont wait
    if(bckgrnd_flag != 0){
      //testing printf("waiting\n");
      waitpid(pid,&status,0);
      //testing printf("child process terminated\n");
    }
  }
  
  
  return 0;
}

/*
Purpose: returns flag indicating if argument list
contains the run in background command

returns 0 if the run in backgrounds command is found
at the end of arguments 

*/
int bckgrnd_check(char ** arg_buff){

  int i = 0;
  
  while(arg_buff[i] != NULL){
    i++;
  }

  return strcmp(arg_buff[i-1], "&");
}

//TO DO: EXECUTE io redirection

void exec_ioredir(char **arg_buff, char ** command_buff){

  if(strcmp(command_buff[0], ">") == 0){
    int fd = open(command_buff[1], O_WRONLY| O_CREAT | O_TRUNC, S_IRWXU);
    dup2(fd,1);
    close(fd);
  }
  else if(strcmp(command_buff[0], "<") == 0 ){
    int fd = open(command_buff[1], O_RDONLY);
    dup2(fd,0);
    close(fd);
  }
  
  return;
}

/*
compares command array with arg_buffer and
returns a number based on the command detected

0 = no commands
1 = pipe
2 = io redirection

If a command is detected, the command buffer is also filled and the
arg buffer is modified to remove the command and its arguments

*/
int command_handler(char **commands,int commands_size,char **arg_buffer, int buff_size, char ** command_buff){

  int status;
  int found = 0;
  
  for(int i = 0; i < buff_size && found != 1; i++){
    if(arg_buffer[i] == NULL){
      break;
    }
    for(int j = 0; j < commands_size && found != 1; j++){
      //if command matches with arg_buffer
      if(strcmp(commands[j],arg_buffer[i]) == 0){
	copy_starting(arg_buffer,command_buff,i);
	found = 1;
	if(strcmp(commands[j],"|") == 0){
	  status = 1;
	}
	else if(strcmp(commands[j],"<") == 0 || strcmp(commands[j],">") == 0){
	  status = 2;
	}
	clear_rest(arg_buffer,buff_size,i);
      }
    }
  }
  if(found == 0){
    status = 0;
  }
  
  return status;
}




/*
set the pointer at index and the pointers that come after
it in buff to NULL
*/
void clear_rest(char ** buff, int buff_size,int index){
  for(int i = index; i < buff_size; i++){
    buff[i] = NULL;
  }
  return;
}

/*
copies content of buff into buff2 starting at an index

 */
void copy_starting(char ** buff, char ** buff2, int index){

  for(int i = index; buff[i] != NULL; i++){
    buff2[i-index] = buff[i];
  }
  return;
}
/*
own strcmp function identical to the library
 */
int strcmp(char *str1, char *str2){

  while (*str1){
    if (*str1 != *str2) {
      break;
    }
    str1++;
    str2++;
  }
  return *(unsigned char*)str1 - *(unsigned char*)str2;
}
   
/*
TODO: 

- seperate execute functions for each type of command 
  (pipe command, regular command (identical to the one above), io redirection,
  maybe built in commands?)

- parse to detect pipe, io redirection or ampersand


 */
int read_input(char *buffer, int buffer_size){
  int status;
  
  if(buffer == NULL){
    status = -1;
    return status;
  }
  else{
   status = read(0,buffer,buffer_size);
  }
  return status;
}

/*
Given an array of char pointers,
Takes the initial input string, tokenizes it with
delimiter (space and newline),and adds a pointer to each token 
in the arg_buffer. 
 */

void get_args(char * str, char **arg_buffer,int arg_buffer_size){

  arg_buffer[0] = strtok(str," \n");
  for(int i = 1; i < arg_buffer_size; i++){
    arg_buffer[i] = strtok(NULL," \n");
    if(arg_buffer[i] == NULL){
      break;
    }
  }
  return;
}
/*
- works the same way as strtok function
 */

char *mystrtok(char *str, const char *delim){

  static char * token;

  if(str != NULL){
    token = str;
  }
  else{
    str = token;
  }

  if(*token == '\0'){
    return NULL;
  }

  while(*token != '\0'){

    for(int i = 0; delim[i] != '\0'; i++){

      if(*token == delim[i]){
      //any multiple leading delimiters skipped
	if(token == str){
	  token++;
	  str++;
	}
	else{
	  *token = '\0';
	  token++;
	  break;
	}
      }
    }

    if(*token == '\0'){
      return str;
    }
    token++;
  }
  return str;
}

