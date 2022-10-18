/* Michael Pottker */

#include <string.h>
#include "student.h"
#include <stdio.h>
Student new_student(const char name[], unsigned int id, float shoe_size)
{
  Student new_student;
  
  if (name == NULL)
  {
    new_student.name[0]= '\0';
  }
  else
  {
    strncpy(new_student.name, name, 39);
  }
  new_student.id= id;
  new_student.shoe_size= shoe_size;

  return new_student;
}

void init_student(Student *const student, const char name[], unsigned int id,
		  float shoe_size)
{
  Student new_student;
  
  if (student)
  {
    if (name == NULL)
      {
	new_student.name[0]= '\0';
      }
    else
      {
	strncpy(new_student.name, name, 39);
      }
    new_student.id= id;
    new_student.shoe_size= shoe_size;
    *student= new_student;
  }
}

unsigned int has_id(Student student, unsigned int id)
{
  if (student.id != id)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

unsigned int has_name(Student student, const char name[])
{
  if (name == NULL)
  {
    return 0;
  }

  if (strcmp(name, student.name) != 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

unsigned int get_id(Student student)
{
  return student.id;
}

float get_shoe_size(Student student)
{
  return student.shoe_size;
}

Student change_shoe_size(Student student, float new_shoe_size)
{
  Student new_student= student;
  new_student.shoe_size= new_shoe_size;
  return new_student;
}

void change_name(Student *const student, const char new_name[])
{
  Student new_student;
  
  if (student)
  {
    new_student= *student;
    if (new_name == NULL)
    {
      new_student.name[0]= '\0';
    }
    else
    {
      strncpy(new_student.name, new_name, 39);
    }
    *student= new_student;
  }
  
}
