/* Michael Pottker*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sysexits.h>
#include <err.h>
#include "safe-fork.h"

int main()
{
  pid_t pid;
  int pipefd[2];
  int num;
  
  pipe(pipefd);
  pid= safe_fork();

  if (pid > 0)
  {
    dup2(pipefd[0], 0);
    close(pipefd[0]);
    close(pipefd[1]);
 
    scanf("%d", &num);
    
    if(num >= 200)
    {
      printf("Long enough!\n");
      exit(0);
    }
    else
    {
      printf("Too short!\n");
      exit(1);
    }  
  }
  else if (pid == 0)
  {
    dup2(pipefd[1], 1);
    close(pipefd[0]);
    close(pipefd[1]);
    execl("/usr/bin/wc", "wc", "-w", NULL);
  }
  else
  {
    printf("ERROR with forking");
  }
  
  return 1;
}
