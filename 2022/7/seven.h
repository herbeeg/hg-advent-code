#ifndef __SEVEN_DOT_H__
#define __SEVEN_DOT_H__

struct directory { 
  char *name;
  int id;
  int parent;
};

struct file {
  int id;
  int parent;
  long int size;
};

typedef enum { changing, listing } mode;

#endif
