#include "input.h"

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
    status = 0;
    return status;
  }
  else
  {
    status = read(0, buffer, buffer_size);
    if(buffer[0] == ' ' || buffer[0] == '\n' || buffer[0] == '\0')
      {
	status = 0;
      };
  }
  return status;
}
