#ifndef __ELEVEN_DOT_H__
#define __ELEVEN_DOT_H__

struct Item {
  unsigned int worry_level;
};

struct Monkey {
  int id;
  struct Item items[36];
  int condition_test;
  int condition_pass;
  int condition_fail;
  int number_of_inspections;
};

typedef enum {
  starting,
  operation,
  divisible,
  iftrue,
  iffalse
} RState;

#endif
