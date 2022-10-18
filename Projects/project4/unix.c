/* Mihcael Pottker */

/* This program creates a Unix filesystem that has a
 * hierarchy of files and directories each filesystem consists
 * of nodes which correspond to files or directories */

#include "unix.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* This creates the Unix filesystem by initializing
 * the root node and setting head and current equal
 * to the root */
void mkfs(Unix *filesystem)
{
  Node *new_node;
  new_node= malloc(sizeof(Node));
  if (new_node)
  {
    new_node->name= malloc(sizeof("/"));
    if (new_node->name)
    {
      strcpy(new_node->name, "/");
      new_node->right= NULL;
      new_node->up= NULL;
      new_node->down= NULL;
      new_node->is_dir= 1;
    }
  }
  filesystem->head= new_node;
  filesystem->current= new_node;
}

/* This creates a file if it doesn't already exist and arg is valid
 * and inserts it in order then returns 1 or returns 1 if arg is 
 * the name of a file/directory that already exists */
int touch(Unix *filesystem, const char arg[])
{
  int retval= 0;
  Node *curr, *prev= NULL, *new_node;

  /* checks that filesystem isn't null and that arg is valid */
  if (filesystem && arg && arg[0] != '\0' && (strlen(arg) > 1
					      && strchr(arg, '/') == NULL))
  {
    if (strcmp(arg, "/") == 0 || strcmp(arg, ".") == 0 ||
	strcmp(arg, "..") == 0)
    {
      return 1;
    }
    curr= filesystem->current->down;

    /* searches through current directory to find the spot that the
     * node should be found or inserted */ 
    while (curr && strcmp(curr->name, arg) < 0)
    {
      prev= curr;
      curr= curr->right;
    }

    /* checks if we got to end of the children of current directory */
    if (curr)
    {
      /* checks that we found the file/ directory */
      if (strcmp(curr->name, arg) == 0)
      {
	  retval= 1;
      }
      /* checks if we are past the spot where the node should be inserted */
      else
      {
	new_node= malloc(sizeof(Node));
	if (new_node)
	{
	  new_node->name= malloc(strlen(arg));
	  if (new_node->name)
	  {
	    new_node->up= filesystem->current;
	    new_node->down= NULL;
	    new_node->is_dir= 0;
	    new_node->right= curr;
	    strcpy(new_node->name, arg);
	    retval= 1;
	    
	    /* checks if we are at the first position or not */ 
	    if (prev)
	    {
	      prev->right= new_node;
	    }
	    else
	    {
	      filesystem->current->down= new_node;
	    }
	  }
	}
      }
    }
    else
    {
      new_node= malloc(sizeof(Node));
      if (new_node)
      {
        new_node->name= malloc(strlen(arg));
        if (new_node->name)
        {
	  new_node->up= filesystem->current;
	  new_node->down= NULL;
	  new_node->is_dir= 0;
	  strcpy(new_node->name, arg);
	  retval= 1;

	  /* checks if we're at first position or not */
	  if (prev)
	  {
	    new_node->right= prev->right;
	    prev->right= new_node;
	  }
	  else
	  {
	    filesystem->current->down= new_node;
	    new_node->right= NULL;
	  }
        }
      }
    }
  }
  return retval;
}

/* this function creates a new directory in the current directory if a file
 * of directory doesn't already exist with the same name. Returns 1 if 
 * a new directory is added, 0 otherwise. */ 
int mkdir(Unix *filesystem, const char arg[])
{
  int retval= 0;
  Node *curr, *prev= NULL, *new_node;

  /* checks if filesystem is null and that arg is valid */
  if (filesystem && arg && arg[0] != '\0' && (strlen(arg) > 1
					      && strchr(arg, '/') == NULL))
  {
    if (strcmp(arg, "/") == 0 || strcmp(arg, ".") == 0 ||
	strcmp(arg, "..") == 0)
    {
      return 0;
    }
    curr= filesystem->current->down;

    /* finds the spot that the node we're looking for or inserting 
     * should be */
    while (curr && strcmp(curr->name, arg) < 0)
    {
      prev= curr;
      curr= curr->right;
    }

    /* checks if we got to end of current directory's children*/
    if (curr)
    {
      /* checks if we found a file/directory with the same name */
      if (strcmp(curr->name, arg) == 0)
      {
	  retval= 0;
      }
      /* insert a new node at that position if it doesn't already exist */
      else
      {
	new_node= malloc(sizeof(Node));
	if (new_node)
	{
	  new_node->name= malloc(4 * strlen(arg));
	  if (new_node->name)
	  {
	    new_node->up= filesystem->current;
	    new_node->down= NULL;
	    new_node->is_dir= 1;
	    new_node->right= curr;
	    strcpy(new_node->name, arg);
	    retval= 1;
	    /* checks if we are at the first element */
	    if (prev)
	    {
	      prev->right= new_node;
	    }
	    else
	    {
	      filesystem->current->down= new_node;
	    }
	  }
	}
      }
    }
    else
    {
      new_node= malloc(sizeof(Node));
      if (new_node)
      {
        new_node->name= malloc(4 * strlen(arg));
        if (new_node->name)
        {
	  new_node->up= (filesystem->current);
	  new_node->down= NULL;
	  new_node->is_dir= 1;
	  strcpy(new_node->name, arg);
	  retval= 1;

	  /* checks if we're at first element */
	  if (prev)
	  {
	    new_node->right= (prev->right);
	    prev->right= new_node;
	  }
	  else
	  {
	    filesystem->current->down= new_node;
	    new_node->right= NULL;
	  }
        }
      }
    }
  }
  return retval;
}

/* this function changes the current directory to the specified directory
 * if it exists and returns 1 if it successfuly changes directory,
 * 0 otherwise. */
int cd(Unix *filesystem, const char arg[])
{
  Node *curr, *mover;
  int retval= 0;

  /* checks that filesystem and arg are not null */
  if (filesystem && arg)
  {
    curr= filesystem->current;
    mover= curr;

    if (strcmp(arg, ".") == 0 || arg[0] == '\0')
    {
      retval= 1;
    }
    
    else if (strcmp(arg, "..") == 0)
    {
      /* checks that we aren't at the root */
      if (curr->up)
      {
	filesystem->current= curr->up;
      }
      retval= 1;
    }
    else if (strcmp(arg, "/") == 0)
    {
      filesystem->current= filesystem->head;
      retval= 1;
    }
    else
    {
      mover= curr->down;

      /* searches until we find where node with name arg should be */
      while (mover && strcmp(mover->name, arg) < 0)
      {
	mover= mover->right;
      }
      
      /* checks that the place we're trying to cd to is actually a 
       * directory and not a file */
      if (mover && strcmp(mover->name, arg) == 0 && mover->is_dir == 1)
      {
	filesystem->current= mover;
	retval= 1;
      }
      /* handles if the place we're trying to cd to is a file, not 
       * directory, or if the specified file doesn't exist in the
       * current directory */
      else if ((mover && strcmp(mover->name, arg) == 0 && mover->is_dir == 0)
	       || !mover)
      {
	retval= 0;
      }
    }
  }
  return retval;
}

/* This function prints all the children of the specified directory */
int ls(Unix *filesystem, const char arg[])
{
  Node *curr, *mover;
  int retval= 0;

  /* checks that filesystem and arg aren't null */
  if (filesystem && arg)
  {
    curr= filesystem->current;
    mover= filesystem->current->down;

    if (strcmp(arg, ".") == 0 || arg[0] == '\0')
    {
      retval= 1;
    }
    
    else if (strcmp(arg, "..") == 0)
    {
      /* handles the case when we are at the root */
      if (curr->up)
      {
	mover= mover->up;
      }
      if (!curr->up)
      {
	mover= mover->down;
      }
      retval= 1;
    }
    else if (strcmp(arg, "/") == 0)
    {
      mover= filesystem->head->down;
      retval= 1;
    }
    else
    {
      mover= filesystem->current->down;

      /* searches until we find where node with name arg should be */ 
      while (mover && strcmp(mover->name, arg) < 0)
      {
	mover= mover->right;
      }

      /* If we found a directory with the name arg 
       * then move the mover down in order to print its children */
      if (mover && strcmp(mover->name, arg) == 0
	  && mover->is_dir == 1)
      {
	mover= mover->down;
	retval= 1;
      }
      /* if the node we were looking for is a file then just 
       * print it and set mover to null so it won't keep printing */
      else if (mover && strcmp(mover->name, arg)== 0
			       && mover->is_dir == 0)
      {
        printf("%s\n", mover->name);
	retval= 1;
	mover= NULL;
      }
      else
      {
	retval= 0;
	mover= NULL;
      }
    }
    /* This will print all the files and directories of the current
     * directory, printing a "/" after each one that is a directory */
    while (mover)
    {  
      printf("%s", mover->name);
      if (mover->is_dir == 1)
      {
	printf("/");
      }
      printf("\n");
      mover= mover->right;
    }
  }

  return retval;
}

/* this function prints the name of the current directory
 * if the parameter isn't null */
void pwd(Unix *filesystem)
{
  if (filesystem)
  {
    printf("%s\n", filesystem->current->name);
  }
}
