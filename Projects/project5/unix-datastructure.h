/* Michael Pottker */ 

#if !defined(UNIX_DATASTRUCTURE_H)
#define UNIX_DATASTRUCTURE_H

/* the "up" in each node refers to its parent, "right"
 * refers to its siblings, "down" refers to its children.
 * is_dir will be set to one if the node is a directory and
 * 0 if the node is a file. */
typedef struct node {
  int is_dir;
  struct node *up;
  struct node *right;
  struct node *down;
  char *name;
} Node;

/* The overarching Unix system that just keeps track 
 * of the root and current directory */
typedef struct {
  Node *head;
  Node *current;
} Unix;

#endif
