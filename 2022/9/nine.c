#include <stdio.h>
#include <stdlib.h>

#include "nine.h"

int main()
{
  FILE *f = fopen("input.txt", "r");
  
  if (NULL == f) {
    exit(0);
  }
  
  char buffer[2000];
  
  struct bridge *bridge_data = malloc(2 * sizeof(struct bridge));
  
  while (NULL != fgets(buffer, 2000, f)) {
    if ('\n' != buffer[0]) {
      
    }
  }
  
  return 0;
}
