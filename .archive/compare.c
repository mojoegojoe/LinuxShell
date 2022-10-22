#include "compare.h"

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