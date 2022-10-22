#include "str_functions.h"


int str_contains(char *string, int str_len, char *toFind, int f_len)
{
  int slen = str_len;
  int tFlen = f_len;
  int found = 0;

  if (slen >= tFlen)
  {
    for (int s = 0, t = 0; s < slen; s++)
    {
      do
      {

        if (string[s] == toFind[t])
        {
          if (++found == tFlen)
            return 1;
          s++;
          t++;
        }
        else
        {
          s -= found;
          found = 0;
          t = 0;
        }

      } while (found);
    }
    return 0;
  }
  else
    return -1;
}

char *str_tok(char *str, const char *delim)
{
  char *spanp;
  int c, sc;
  char *tok;
  static char *last;

  if (str == NULL && (str = last) == NULL)
    return (NULL);

  /*
   * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
   */
cont:
  c = *str++;
  for (spanp = (char *)delim; (sc = *spanp++) != 0;)
  {
    if (c == sc)
      goto cont;
  }

  if (c == 0)
  { /* no non-delimiter characters */
    last = NULL;
    return (NULL);
  }
  tok = str - 1;

  /*
   * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
   * Note that delim must have one NUL; we stop if we see that, too.
   */
  for (;;)
  {
    c = *str++;
    spanp = (char *)delim;
    do
    {
      if ((sc = *spanp++) == c)
      {
        if (c == 0)
          str = NULL;
        else
          str[-1] = 0;
        last = str;
        return (tok);
      }
    } while (sc != 0);
  }
  /* NOTREACHED */
}

char *strcpy(char *destination, const char *source)
{
  // return if no memory is allocated to the destination
  if (destination == NULL)
  {
    return NULL;
  }

  // take a pointer pointing to the beginning of the destination string
  char *ptr = destination;

  // copy the C-string pointed by source into the array
  // pointed by destination
  while (*source != '\0')
  {
    *destination = *source;
    destination++;
    source++;
  }

  // include the terminating null character
  *destination = '\0';

  // the destination is returned by standard `strcpy()`
  return ptr;
}

int str_cpy(char *BUFFER, char *SRC, char *delim)
{
  int i = 0;
  if (!BUFFER || !SRC)
  {
    print_line("NO BUFFER TO COPY", delim, 2);
  }
  while (SRC[i] != delim[2] && i <= BUFFERSIZE)
  {
    BUFFER[i] = SRC[i];
    i++;
  }
  if (SRC[i] != delim[2])
  { // reached end of buffer before end of src
    print_line("ERROR SRC CPY NOT COMPLETE - STR TO LONG FOR BUFFER\n", delim, 2);
    return 1;
  }
  while (i < BUFFERSIZE)
  {
    BUFFER[i] = '\0'; // ends str copy
    i++;
  }
  return 0;
}
int strcmp(char *str1, char *str2)
{

  while (*str1)
  {
    if (*str1 != *str2)
    {
      break;
    }
    str1++;
    str2++;
  }
  return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void clear_rest(char **buff, int buff_size, int index)
{
  for (int i = index; i < buff_size; i++)
  {
    buff[i] = NULL;
  }
  return;
}

void clear_buffer(char buff[], int buff_size, int index)
{
  for (int i = index; i < buff_size; i++)
  {
    buff[i] = 0;
  }
  return;
}
/*
copies content of buff into buff2 starting at an index

 */
void copy_starting(char **buff, char **buff2, int index)
{

  for (int i = index; buff[i] != NULL; i++)
  {
    buff2[i - index] = buff[i];
  }
  return;
}
