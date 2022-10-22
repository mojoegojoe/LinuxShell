 #include "error.h"

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