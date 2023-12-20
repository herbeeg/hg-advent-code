#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eleven.h"

int main()
{
  FILE *f = fopen("input.txt", "r");
  
  char buffer[100];
  
  if (NULL == f) {
    exit(0);
  }
  
  struct Monkey *monkeys[8];
  int m_ptr = -1;
  
  char next_struct[7];
  strcpy(next_struct, "Monkey\0");
  
  RState read_state = starting;
  
  while (NULL != fgets(buffer, 100, f)) {
    if ('\n' != buffer[0]) {
      if (0 == strncmp(buffer, next_struct, 6)) {
        m_ptr++;
      } else {
        if (starting == read_state) {
          read_state = operation;
        } else if (operation == read_state) {
          read_state = divisible;
        } else if (divisible == read_state) {
          read_state = iftrue;
        } else if (iftrue == read_state) {
          read_state = iffalse;
        } else if (iffalse == read_state) {
          read_state = operation;
        }
      }
    }
  }
   
  return 0;
}
