#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *strtok(char *str, const char *delim);
void get_args(char * str, char **arg_buffer);

#define  BUFF_SIZE 30

int main(){

  char input_buff[BUFF_SIZE];
  char *arg_buff[BUFF_SIZE];
  pid_t pid;
  int status;
  int running = 1;

  //test main shell loop
  while(running){

    //replace printf with our write function
    printf("$ ");

    //replace fgets with our input function
    if(fgets(input_buff,BUFF_SIZE,stdin) != NULL){
      pid = fork();
      if(pid == 0){
	get_args(input_buff,arg_buff);
	execve(arg_buff[0],arg_buff,NULL);
      }
      waitpid(pid,&status,0);
      
    }

  }
  return 0;
}

/*
TODO: 

- seperate execute functions for each type of command 
  (pipe command, regular command (identical to the one above), io redirection,
  maybe built in commands?)

- parse to detect pipe, io redirection or ampersand


 */

/*
Given an array of char pointers,
Takes the initial input string, tokenizes it with
delimiter (space and newline),and adds a pointer to each token 
in the arg_buffer. 
 */

void get_args(char * str, char **arg_buffer){

  arg_buffer[0] = strtok(str," \n");
  for(int i = 1; i < BUFF_SIZE; i++){
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

