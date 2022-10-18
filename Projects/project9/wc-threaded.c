/* Michael Pottker */

#include <stdio.h>
#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

typedef struct input {
  FILE *f;
  int lines;
  int chars;
  int words;
} C_Input;


static void *wc(void *args);

static void *wc(void *args)
{
  char ch, next_ch;
  
  C_Input *in;
  in= args;
  
  if (in->f != NULL)
  {
    in->lines= in->words= in->chars= 0;

    ch= fgetc(in->f);
    while (!feof(in->f))
    {
      next_ch= fgetc(in->f);
      ungetc(next_ch, in->f); 
            
      if (ch == '\n')
	in->lines++;

      /* if the current character is not whitespace but the next character
	 is, or if the current character is not whitespace and it is the
	 last character in the input, the word count increases */
      if (!isspace(ch) && (isspace(next_ch) || feof(in->f)))
	in->words++;

      in->chars++;

      ch= fgetc(in->f);
    }
    fclose(in->f);
  }

  return in;
}

int main(int argc, char *argv[]) {
  char *filename;
  int arg_num= 1,total_lines= 0, total_words= 0, total_chars= 0;
		  
  int i;

  C_Input *in;
  void *ptr;
   
  pthread_t *threads= malloc(sizeof(threads) * (argc - 1));
  
  while (arg_num < argc)
  {
    filename= argv[arg_num++];

    in= malloc(sizeof(C_Input));
    in->f= fopen(filename, "r");
    
    pthread_create(&threads[arg_num - 2], NULL, wc, in);
  }
  
  for (i= 1; i < arg_num; i++)
  {
    pthread_join(threads[i - 1], &ptr);
    in= ptr;

    total_lines += in->lines;
    total_words += in->words;
    total_chars += in->chars;
    
    free(in);
  }
  free(threads);
   
  printf("%4d %4d %4d\n", total_lines, total_words, total_chars);

  return 0;
}
