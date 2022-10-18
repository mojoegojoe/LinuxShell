#include "parser.h"




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

  arg_buffer[0] = str_parser(str," \n");
  for(int i = 1; i < BUFF_SIZE; i++){
    arg_buffer[i] = str_parser(NULL," \n");
    if(arg_buffer[i] == NULL){
      break;
    }
  }


  return;
}

/*
- works the same way as strtok function
 */

char *str_parser(char *str, const char *delim){

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