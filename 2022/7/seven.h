#ifndef __SEVEN_DOT_H__
#define __SEVEN_DOT_H__

struct directory { 
  char name[32];
  int id;
  int parent;
  int child_ids[32];
  int num_of_children;
  signed long long int local_size;
};

struct file {
  int id;
  int parent;
};

#endif
