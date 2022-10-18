#include "io.h"



char read_line(char BUFFER[BUFFERSIZE], char delim[3]){
  // while non terminated input store each value of stream into the given buffer
  int i = 0;
  char c;
//   printf("mysh $: ");

  if(!BUFFER){
    // printf("memory allocation error - no buffer");
    print_line("memory allocation error - no buffer", 35);
    exit(EXIT_FAILURE);
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
  
  print_line("BUFFER FULL\n\0", &delim);
  return *BUFFER;
}


int print_line(char BUFFER[BUFFERSIZE], char delim[3]){
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

int error_line(char BUFFER[BUFFERSIZE], char delim[3]){
  // write error line and add err number to end.
  int errorcode = errno;
  if(!errorcode){
    printf("NO VALID ERROR CODE\n");
    return -1;
  }
  perror("Error : \n");
  putc(errorcode, stderr);
  return 0;
}

int buff_cmp(char BUFFER1[BUFFERSIZE],char BUFFER2[BUFFERSIZE], char delim[3]){
  int i = 0;
  while(BUFFER1[i] == BUFFER2[i] && i < BUFFERSIZE && BUFFER1[i] != delim[2]){
    i++;
  }
  if(i==BUFFERSIZE || BUFFER1[i] == delim[2]){
    return 0;
  }
  printf("failed cmp at pt: %d", i);
  return -1;
}

int str_cpy(char BUFFER[BUFFERSIZE],char SRC[BUFFERSIZE], char delim[3]){
  int i = 0;
  while(SRC[i] != delim[2] && i < BUFFERSIZE){
    BUFFER[i] = SRC[i];
    i++;
  }
  if(SRC[i] != delim[2]){ // reached end of buffer before end of src
    printf("ERROR SRC CPY NOT COMPLETE - STR TO LONG FOR BUFFER\n");
    return -1;
  }
  BUFFER[i] = '\0'; // ends str copy
  return 0;
}