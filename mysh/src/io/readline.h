#ifdef IO_HEADER
#define IO_HEADER

int read_line(char *BUFFER, char *delim);
int print_line(char *BUFFER, char *delim);
int error_line(char *BUFFER, char *delim);
int buff_cmp(char *BUFFER1, char *BUFFER2, char *delim);
int str_cpy(char *BUFFER, char *SRC, char *delim);

#endif
