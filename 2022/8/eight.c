#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false, true } bool;

int main()
{
  FILE *f = fopen("input.txt", "r");
  
  if (NULL == f) {
    exit(0);
  }
  
  int matrix[99][99];
  char buffer[100];
  
  int x_ptr = 0;
  int y_ptr = 0;
  
  int visible_trees = 0;
  
  while (NULL != fgets(buffer, 100, f)) {
    if ('\n' != buffer[0]) {
      char *tmp_buffer = buffer;
      
      for (int b_ptr = 0; (int) strlen(tmp_buffer) >= b_ptr; b_ptr++) {
        char *single = malloc(2);
        single[0] = tmp_buffer[b_ptr];
        single[1] = '\0';
        
        int val = atoi(single);
        matrix[y_ptr][b_ptr] = val;
      }
      
      y_ptr++;
    }
  }
  
  for (int y = 0; 99 > y; y++) {
    y_ptr = y;
    
    for (int x = 0; 99 > x; x++) {
      x_ptr = x;
      
      // Automatically add all tiles around the edge of the matrix
      // to the number of visible trees as they are all on the
      // outside in the field of view.
      if (
        0 == y ||
        98 == y ||
        0 == x ||
        98 == x
      ) {
        visible_trees++;
      } else {
        //
      }
    }
  }
  
  printf("The number of trees that are visible from outside the grid is %d", visible_trees);
  
  return 0;
}
