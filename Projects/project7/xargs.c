/* Michael Pottker */

/* This program reads arguments from the command line,
 * then executes the command if there is one, or executes
 * echo if there are no command line arguments. It does this
 * by forking a child that will replace itself with the 
 * proper command. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <sysexits.h>
#include <string.h>
#include "safe-fork.h"
#include "split.h"
#include <wait.h>

int main(int argc, char *argv[])
{
  int i= 0, status;
  char *placeholder= malloc(1);
  char *argname= malloc(1);
  char chars_in_line[1000];
  char **strs;
  pid_t pid;

  placeholder[0]= '\0';

  /* checks if there are any command line arguments other than
   * just the name of the program */
  if (argc > 1)
  {
    /* checks if it needs to run in line at a time mode
     * and in this case when the only argument is "-i"
     * so echo should be used */
    if (strcmp(argv[1], "-i") == 0 && argc == 2)
    {
      /* free argname so no memory leaks */
      free(argname);

      /* reads in the input line by line and allocates the correct amount 
       * of memory to store it along with echo as the first word so that
       * execvp works. The input is read into chars_in_line */
      while (fgets(chars_in_line, 1000, stdin))
      {
	argname= malloc(strlen("echo") + strlen(chars_in_line) + 3);
	strcpy(argname, "echo ");
	strcat(argname, chars_in_line);
	
	strs= split(argname);

	pid= safe_fork();

	/* the parent process */
	if (pid > 0)
	{
	  wait(&status);

	  /* needs to free argname every time since its in a loop */
	  free(argname);

	  i= 0;
	  /* frees every element in strs that split allocated */
	  while (strs[i])
	  {
	    free(strs[i]);
	    i++;
	  }
	  free(strs);

	  /* if there was a problem with exec, then exit immediately
	   * and don't read rest of input */
	  if (status)
	  {
	    free(placeholder);
	    exit(1);
	  }
	}
	/* child process replaces itself with echo */
	else if (pid == 0)
	{
	  execvp("echo", strs);
	}
      }
      /* if execution gets here then that means everything worked so 
       * placeholder needs to be freed and program exits successfully */
      free(placeholder);
      exit(0);
    }

    /* checks if it should run it line-at-a-time mode and, in this case, 
     * if there are arguments other than "-i" that need to be executed */
    else if (strcmp(argv[1], "-i") == 0 && argc > 2)
    {
      /* this loop stores the arguments from the command line besides -i */
      for(i = 2; i < argc; i++)
      {
	argname= realloc(argname, strlen(argname) + strlen(argv[i] + 3));
	strcat(argname, argv[i]);
	strcat(argname, " ");
      }

      /* reads in any input and stores alocates space for it. The input 
       * is read into chars_in_line  */
      while (fgets(chars_in_line, 1000, stdin))
      {
	/* uses a temp char variable so that it doesn't have to go through 
	 * a loop every time to allocate argname */
	char *temp= malloc(strlen(argname) + 1);
	strcpy(temp, argname);

	/* placeholder will hold all of the input read and the command line
	 * arguments from temp */
	placeholder= malloc(strlen("") + 1);
	placeholder= realloc(placeholder, strlen(placeholder)
			     + strlen(temp) + 2);
	strcpy(placeholder, temp);
        placeholder= realloc(placeholder, strlen(placeholder)
			     + strlen(chars_in_line) + 2);

	chars_in_line[strlen(chars_in_line) - 1]= ' ';
	strcat(placeholder, chars_in_line);
        
	strs= split(placeholder);

	pid= safe_fork();

	/* parent process */
	if (pid > 0)
	{
	  wait(&status);

	  /* frees the necessary variables every time */
	  free(placeholder);
	  free(temp);

	  i= 0;
	  /* frees each element in strs from split */
	  while (strs[i])
	  {
	    free(strs[i]);
	    i++;
	  }
	  free(strs);

	  /* if the child exits with an error than parent exits 
	   * immediately with error status and frees argname */
	  if (status)
	  {
	    free(argname);
	    exit(1);
	  }
	}
	/* child process replaces itself with the program command */
	else if (pid == 0)
	{
	  execvp(argv[2], strs);
	  exit(1);
	}
      }

      /* if execution gets down here then that means there were no errors so
       * so argname is freed and exit with successful status */ 
      free(argname);
      exit(0);
    }
    /* this else is if -i isn't used but there is a command line argument */
    else
    {
      /* reads the input into chars_in_line and allocates memory
       * for placeholder */
      while (fgets(chars_in_line, 1000, stdin))
      {
	placeholder= realloc(placeholder, strlen(placeholder)
			     + strlen(chars_in_line) + 2);
	chars_in_line[strlen(chars_in_line) - 1]= ' ';
	strcat(placeholder, chars_in_line);
      }

      /* copies a new line at the end of placeholder */
      placeholder= realloc(placeholder, strlen(placeholder) + 2);
      strcat(placeholder, "\n");

      /* allocates memory for argname and copies the command line
       * args into it */
      for(i = 1; i < argc; i++)
      {
	argname= realloc(argname, strlen(argname) + strlen(argv[i] + 3));
	strcat(argname, argv[i]);
	strcat(argname, " ");
      }

      argname= realloc(argname, strlen(placeholder) + strlen(argname) + 2);
      strcat(argname, placeholder);

      strs= split(argname);
      
      pid= safe_fork();

      /* parent process */
      if (pid > 0)
      {
	wait(&status);
	
	i= 0;
	/* frees each element in strs from split */
	while (strs[i])
	{
	  free(strs[i]);
	  i++;
	}

	/* free everything else */
	free(argname);
	free(strs);
	free(placeholder);

	/* if the child had an error then exit with 
	 * status 1 or if child executes successfully 
	 * then exit with status 0 */
	if (status)
	{
	  exit(1);
	}
	else
	{
	  exit(0);
	}
      }
      /* child process replaces itself with the command 
      * from the command line */
      else if (pid == 0)
      {
	execvp(argv[1], strs);
      }
      else
      {
	err(EX_OSERR, "FORK ERROR");
      }
    }
  }
  else
  {
    /* frees argname and just copies echo into it and allocates memory
     * for it*/
    free(argname);
    argname= NULL;
    argname= malloc(strlen("echo") + 2);
    strcpy(argname, "echo ");

    /* reads the input into chars_in_line and allocates space for placeholder
     * which holds has chars_in_line concatenated to it */
    while (fgets(chars_in_line, 1000, stdin))
    {
      placeholder= realloc(placeholder, strlen(placeholder)
			   + strlen(chars_in_line) + 1);
      chars_in_line[strlen(chars_in_line) - 1]= ' ';
      strcat(placeholder, chars_in_line);
    }
    /* puts a new line at the end of placeholder and then concatenates
     * placeholder to argname */ 
    placeholder= realloc(placeholder, strlen(placeholder) + 3);
    strcat(placeholder, "\n");
    argname= realloc(argname, strlen(placeholder) + strlen(argname) + 2);
    strcat(argname, placeholder);

    strs= split(argname);
    
    pid= safe_fork();

    /* parent process */
    if (pid > 0)
    {
      wait(&status);

      /* frees everything it needs to then frees 
       * each element is strs that it got from split */
      free(argname);
      free(placeholder);
      i= 0;
      while (strs[i])
      {
	free(strs[i]);
	i++;
      }
      free(strs);

      /* exits with success status */
      exit(0);
    }
    else if (pid == 0)
    {
      execvp("echo", strs);
    }
    else
    {
      err(EX_OSERR, "FORK ERROR");
    }
  }
  return 1;
}
