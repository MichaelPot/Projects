/* Michael Pottker */

/* This program creates a Linked List along with some functions used 
 * to change or get details about the list using a linked list with
 * a dummy head node. (Note: I use "node" in some of the function comments
 * because I am treating each List struct as a node in a Linked List)
 */

/* List definition from list.h 
	typedef struct list {
		int data;
		struct list *next;
	} List;
*/

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/* initializes the list by making a dummy head node 
 * if list isn't null
 */
void init(List *const list)
{
  if (list)
  {
    list->next= NULL;
  }
}

/* append a new list struct onto the list by first checking if list
 * parameter is null, then traversing through the list if it isn't null 
 * until it reaches the end then appends a new list struct with new_value 
 * in it by allocating memory and adjusting pointers
 */
int append(List *const list, int new_value)
{
  List *curr, *prev, *new_list;

  if (list)
  {
    curr= list->next;
    prev= list;
    
    while (curr)
    {
      prev= curr;
      curr= curr->next;
    }
    
    new_list= malloc(sizeof(*list));
    if (new_list)
    {	
      prev->next= new_list;
      new_list->data= new_value;
      new_list->next= NULL;
      return 1;
    }
  }
  return 0;
}

/* checks if list parameter is null and if it isn't then 
 * this adds a new list struct at the beginning of the list 
 * by allocating memory and adjusting pointers 
 */  
int prepend(List *const list, int new_value)
{
  List *new_list;

  if (list)
  {
    new_list= malloc(sizeof(*list));
    if (new_list)
    {
      new_list->next= list->next;
      new_list->data= new_value;
      list->next= new_list;
      return 1;
    }
  }
  return 0;
}

/* returns the size of the list by traversing through
 * it and incrementing a counter, ignoring the dummy head node. 
 * Returns 0 if list is null
 */
int size(List *const list)
{
  int count= 0;
  List *curr;
  
  if (list)
  {
    curr= list->next;
    while (curr)
    {
      curr= curr->next;
      count++;
    }
  }
  return count;
}

/* prints the list in order from the first node (not the dummy
 * head node) if the list isn't null by traversing it and checking
 * if we reached the last node so it won't print another space and
 * instead print a new line.
 */
void print(List *const list)
{
  List *curr;

  if (list)
  {
    curr= list->next;

    while (curr)
    {
      if (curr->next)
      {
	printf("%d ", curr->data);
      }
      else
      {
	printf("%d\n", curr->data);
      }
      curr= curr->next;
    }
  }
}

/* finds a specified value in a list if it is present
 * and returns its position if it is there, -1 if it
 * isn't in the list, and 0 if the list is null
 */
int find(List *const list, int value)
{
  List *curr;
  int pos= 0;
  
  if (list)
  {
    curr= list->next;

    while (curr && (curr->data != value))
    {
      curr= curr->next;
      pos++;
    }

    if (!curr)
    {
      return -1;
    }
  }
  return pos;
}

/* deletes the list struct at the specified position
 * as long as position is valid and list isn't null.
 * decrements position as it traverses the list in order
 * to find the correct position and ensure that position
 * is valid. Then checks if curr is null to see if we got
 * past the end of the list.
 */
int delete(List *const list, unsigned int position)
{
  List *curr, *prev= list;;

  if (list)
  {
    if (position >= 0)
    {
      curr= list->next;

      while (curr && position  > 0)
      {
	prev= curr;
	curr= curr->next;
	position--;
      }

      /* checks if we got past end of the list 
       * and if it didn't, then deletes the element
       * and frees the memory       
       */
      if (curr)
      {
	prev->next= curr->next;
	free(curr);
	return 1;
      }
    }
  }
  return 0;
}
