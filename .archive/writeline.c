#include "constants.h"
#include "writeline.h"

int write_line(char BUFFER[], char delim[3]){
  // write each char of the length defined output to screen
  int i = 0;
  char c;
  
  if(!BUFFER){
    return -1;
  }
  while(i<=BUFFERSIZE){
    c = putchar(BUFFER[i]);
    if(c == EOF || c == delim[2]){
      return 0;
    }
    i++;
  };
  
  return -1;
}