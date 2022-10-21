#include "readline.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int BUFFERSIZE = 256;
/********************************************************
/    @FUNCION read_line
/    @input   BUFFER - Pointer to a defined char array
/             delim  - Pointer to an array of delimitors
/                       function set by arr[2]
/    @output  bool   - read line pass/fail boolean  
/    @method  For each terminal line we copy a str to
/                       a local buffer then print to user.
/              If no root buffer given a error flag is set
/                        else the local buffer is cleared.
/         and while there is space in the root buffer 
/                                   we read in user input.
/
********************************************************/
int read_line(char *BUFFER, char *delim){
  // while non terminated input store each value of stream into the given buffer
  int i, j = 0;
  int localSize = 10;
  char localBUFF[BUFFERSIZE];
  int EXIT_FAILURE = 2;
  str_cpy(localBUFF,"mysh$: \0",delim);
  
  print_line(localBUFF,delim);
  
  if(!BUFFER){
    print_line("Memory allocation error - no buffer given\n\0", delim);
    _exit(EXIT_FAILURE);
    return 1;
  }
  str_cpy(localBUFF,"\0",delim);

  while(i < BUFFERSIZE){
    read(0, localBUFF, localSize);
    for(j = 0; j < localSize; j++){ // for each char in local buff and add to main BUFF
       BUFFER[i] = localBUFF[j];
       if(BUFFER[i] == delim[2]){ // local buff not full so input complete
      	 return 0;
       }
       i++;
    }
    // keep reading from local buff
  };
  
  // error mesages need changed
  print_line("Memory allocation error - buffer full\n\0", delim);

  return 1;
}

/********************************************************
/    @FUNCION print_line
/    @input   BUFFER - Pointer to a defined char array
/             delim  - Pointer to an array of delimitors
/                       function set by arr[2]
/    @output  bool   - read line pass/fail boolean  
/    @method  If no root buffer given a error flag is set
/             while there is space left on the root buffer 
/                                  we write in user output.
/
********************************************************/
int print_line(char *BUFFER, char *delim){
  // write each char of the length defined output to screen
  int i = 0;
  if(!BUFFER){
    return 1;
  }
  while(i<=BUFFERSIZE){
    if(BUFFER[i] == delim[2]){
      return 0;
    }
    write(1, &BUFFER[i], 1);
    i++;
  };
  
  return 1;
}

/********************************************************
/    @FUNCION error_line
/    @input   BUFFER - Pointer to a defined char array
/             delim  - Pointer to an array of delimitors
/                       function set by arr[2]
/    @output  bool   - read line pass/fail boolean  
/    @method  If no error code is gevin a generic error msg
/             Error code ref from perror function in stdio 
/          If no root buffer given a error flag is returned
/             While there is space in the root buffer 
/                                    we write error to stderr.
/
********************************************************/
int error_line(char *BUFFER, char *delim){
  // write error line and add err number to end.
  int i = 0;
  int errorcode = errno;
  if(!errorcode){
    print_line("Err - No ID Code\n\0", delim);
    return 1;
  }
  perror(BUFFER);
  if(!BUFFER){
    return 1;
  }
  while(i<BUFFERSIZE){
    write(2, &BUFFER[i], 1);
    if(BUFFER[i] == delim[2]){
      write(2, &errorcode, 4);
      return 0;      
    }
    i++;
  };
  return 1;
}


/********************************************************
/    @FUNCION buff_cmp
/    @input   BUFFER1 - Pointer to a defined char array
/             BUFFER2 - Pointer to a defined char array
/             delim  - Pointer to an array of delimitors
/                       function set by arr[2]
/    @output  bool   - read line pass/fail boolean  
/    @method  For two given buffer pointers we cycle through
/              array till Buffersize is exceded or we reach 
/               the end of an str or comparison block.
/             If we reach the end of the buffer or str 
/                                   return true
/               else buffers are not compariable
/
********************************************************/
int buff_cmp(char *BUFFER1,char *BUFFER2, char *delim){
  int i = 0;
  while(BUFFER1[i] == BUFFER2[i] && i < BUFFERSIZE && BUFFER1[i] != delim[2]){
    i++;
  }
  if(i==BUFFERSIZE || BUFFER1[i] == delim[2]){
    return 0;
  }
  return 1;
}


/********************************************************
/    @FUNCION str_cpy
/    @input   BUFFER - Pointer to a defined char array
/             SRC    - Pointer to a defined source array
/             delim  - Pointer to an array of delimitors
/                       function set by arr[2]
/    @output  bool   - read line pass/fail boolean  
/    @method  For each char in the src array we copy to the 
/              corisponindng positon in the root array.
/            If no buffers given a error flag is set
/                        else the local buffer is cleared.
/             fills remaining buffer with null.
********************************************************/
int str_cpy(char *BUFFER,char *SRC, char *delim){
  int i = 0;
  if(!BUFFER || !SRC){
    error_line("NO BUFFER TO COPY", delim);
  }
  while(SRC[i] != delim[2] && i <= BUFFERSIZE){
    BUFFER[i] = SRC[i];
    i++;
  }
  if(SRC[i] != delim[2]){ // reached end of buffer before end of src
    error_line("ERROR SRC CPY NOT COMPLETE - STR TO LONG FOR BUFFER\n", delim);
    return 1;
  }
  while(i<BUFFERSIZE){
     BUFFER[i] = '\0'; // ends str copy
     i++;
  }
  return 0;
}
