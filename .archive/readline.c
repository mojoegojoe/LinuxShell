#include "readline.h"


char read_line(char BUFFER[BUFFERSIZE], char delim[3]){
  // while non terminated input store each value of stream into the given buffer
  int i = 0;
  char c;
  printf("mysh $: ");

  if(!BUFFER){
    // printf("memory allocation error - no buffer");
    write_line("memory allocation error - no buffer", 35);
    exit_shell(exit_shell_FAILURE);
  }

  while(i < BUFFERSIZE){
    c = getchar();
    if( c == EOF || c == delim[0] || c == delim[2]){
      BUFFER[i] = delim[3];
      return *BUFFER;
    }else{
      BUFFER[i] = c;
    }
    i++;
  };
  
  write_line("BUFFER FULL\n\0", &delim);
  return *BUFFER;
}





