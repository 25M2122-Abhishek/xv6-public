#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFSIZE 512
char buf[BUFSIZE];
char key[] = "ping";

int strncmp(const char *p, const char *q, uint n)
{
  while (n > 0 && *p && *p == *q)
    n--, p++, q++;
  if (n == 0)
    return 0;
  return (uchar)*p - (uchar)*q;
}

void ping_pong(int fd)
{
  int i, n;
  char word[512];
  int wlen = 0;

  while ((n = read(fd, buf, sizeof(buf))) > 0)
  {
    for (i = 0; i < n; i++)
    {
      if (strchr(" \r\t\n\v", buf[i]))
      {
        if (wlen > 0)
        {
          word[wlen] = '\0';
          if (strncmp(word, key, 4) == 0)
          {
            printf(1, "pong\n");
          }
          wlen = 0;
        }
      }
      else
      {
        word[wlen++] = buf[i];
      }
    }
  }

  if (n < 0)
  {
    printf(1, "pingpong: read error\n");
    exit();
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf(1, "Usage: %s <input_file>\n", argv[0]);
    exit();
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd < 0)
  {
    printf(1, "Error opening file %s\n", argv[1]);
    exit();
  }

  ping_pong(fd);
  close(fd);
  exit();
}
