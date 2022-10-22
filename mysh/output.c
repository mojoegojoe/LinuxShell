#include "output.h"
/********************************************************
/    @FUNCION print_line
/    @input   BUFFER - Pointer to a defined char array
/             delim  - Pointer to an array of delimitors
/                       function set by delim[0]
/    @output  bool   - read line pass/fail boolean
/    @method  If no root buffer given a error flag is set
/             while there is space left on the root buffer
/                                  we write in user output.
/
********************************************************/
int print_line(char *BUFFER, char *delim, int fd)
{
  // write each char of the length defined output to screen
  int i = 0;
  if (!BUFFER)
  {
    return 1;
  }
  while (i <= BUFFERSIZE)
  {
    if (BUFFER[i] == delim[0])
    {
      return 0;
    }
    write(fd, &BUFFER[i], 1);
    i++;
  };

  return 1;
}
