
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

int passwd(char *data, size_t len);

int main() 
{
  char buf[10];

  gets(buf);

  passwd(buf, strlen(buf));
  return 0;
}
