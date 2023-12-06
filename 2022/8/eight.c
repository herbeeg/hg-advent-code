#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eight.h"

int matrix[99][99];

/*
 * Switch the direction to scan the matrix based on the provided
 * enum value and the 2D-array position.
 */
bool Check_Visibility(direction d, int start_x, int start_y)
{
  switch (d) {
    case left:
    {
      // We don't want to compare the matrix position against itself
      // as that will always fail.
      int x_neg = start_x - 1;
      
      while (x_neg >= 0) {
        if (matrix[start_y][x_neg] >= matrix[start_y][start_x]) {
          return false;
        }
        
        x_neg--;
      }
      
      break;
    }
    case right:
    {
      int x_pos = start_x + 1;
      
      while (x_pos < 99) {
        if (matrix[start_y][x_pos] >= matrix[start_y][start_x]) {
          return false;
        }
        
        x_pos++;
      }
      
      break;
    }
    case up:
    {
      int y_neg = start_y - 1;
      
      while (y_neg >= 0) {
        if (matrix[y_neg][start_x] >= matrix[start_y][start_x]) {
          return false;
        }
        
        y_neg--;
      }
      
      break;
    }
    case down:
    {
      int y_pos = start_y + 1;
      
      while (y_pos < 99) {
        if (matrix[y_pos][start_x] >= matrix[start_y][start_x]) {
          return false;
        }
        
        y_pos++;
      }
      
      break;
    }
    default: { break; }
  }
  
  return true;
}

int main()
{
  FILE *f = fopen("input.txt", "r");
  
  if (NULL == f) {
    exit(0);
  }
  
  char buffer[100];
  
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
    for (int x = 0; 99 > x; x++) {
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
        if (
          true == Check_Visibility(left, x, y) ||
          true == Check_Visibility(right, x, y) ||
          true == Check_Visibility(up, x, y) ||
          true == Check_Visibility(down, x, y)
        ) {
          visible_trees++;
        }
      }
    }
  }
  
  printf("The number of trees that are visible from outside the grid is %d", visible_trees);
  
  return 0;
}
