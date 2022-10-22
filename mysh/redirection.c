#include "redirection.h"

int check_redirection(char *command)
{
  unsigned char out = str_contains(command, BUFF_SIZE, ">", 1);
  unsigned char in = str_contains(command, BUFF_SIZE, "<", 1);

  if ((out > 0) && (in > 0))
    return 3;

  else if (out > 0)
    return 2;

  else if (in > 0)
    return 1;

  else
    return 0;
}
void exec_ioredir(char **arg_buff, char **command_buff, int bckgrnd_flag)
{

  if (strcmp(command_buff[0], ">") == 0)
  {
    int saved = dup(1);
    int fd = open(command_buff[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    dup2(fd, 1);
    close(fd);

    runprocess(arg_buff, bckgrnd_flag);
    // restore buffer
    dup2(saved, 1);
    close(saved);
  }
  else if (strcmp(command_buff[0], "<") == 0)
  {
    int saved = dup(0);
    int fd = open(command_buff[1], O_RDONLY);
    dup2(fd, 0);
    close(fd);

    runprocess(arg_buff, bckgrnd_flag);
    dup2(saved, 0);
    close(saved);
  }

  return;
}
