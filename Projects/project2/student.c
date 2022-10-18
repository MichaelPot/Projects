#include "student.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Student *new_student(const char name[], unsigned int id, float shoe_size)
{
  Student *student= malloc(sizeof(*student));

  if (name == NULL)
  {
    student->name= malloc(sizeof(name));
    student->name[0]= '\0';
  }
  else
  {
    student->name= malloc(strlen(name));
    strcpy(student->name, name);
  }
  printf("%s", student->name);
  student->id= id;
  student->shoe_size= shoe_size;
  return student;
}

unsigned int has_id(Student *const student, unsigned int id)
{
  if (student)
  {
    if (student->id == id)
    {
      return 1;
    }
  }
  return 0;
}

unsigned int has_name(Student *const student, const char name[])
{
  if (student && name)
  {
    if (strcmp(name, student->name) == 0)
    {
      return 1;
    }
  }
  return 0;
}

unsigned int get_id(Student *const student)
{ 
  if (student)
  {    
    return student->id;
  }
  return 0;
}

float get_shoe_size(Student *const student)
{
  if (student)
  {
    return student->shoe_size;
  }
  return 0;
}

void change_shoe_size(Student *const student, float new_shoe_size)
{
  if (student)
  {
    student->shoe_size= new_shoe_size;
  }
}

void change_name(Student *const student, const char new_name[])
{
  if (student)
  {
    free(student->name);

    if (new_name == NULL)
    {
      student->name= malloc(sizeof(new_name));
      student->name[0]= '\0';
    }
    else
    {
      student->name= malloc(strlen(new_name));
      strcpy(student->name, new_name);
    }
  }
}

void copy_student(Student *student1, Student *const student2)
{
  if (student1 && student2)
  {
    free(student1->name);
    student1->name= malloc(strlen(student2->name));
    if (student2->name == NULL)
    {
      student1->name[0]= '\0';
    }
    else
    {
      strcpy(student1->name, student2->name);
    }
    student1->id= student2->id;
    student1->shoe_size= student2->shoe_size;
  }
}
