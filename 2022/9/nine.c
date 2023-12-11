#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nine.h"

struct visited *bridge_data;

bool Tail_Should_Move(int hX, int hY, int tX, int tY, facing dir)
{
  switch(dir) {
    case up:
    {
      if ((hY + 1) < tY) {
        return true;
      }
      
      break;
    }
    case right:
    {
      if (hX > (tX + 1)) {
        return true;
      }
      
      break;
    }
    case down:
    {
      if (hY > (tY + 1)) {
        return true;
      }
      
      break;
    }
    case left:
    {
      if ((hX + 1) < tX) {
        return true;
      }
      
      break;
    }
    default: { return false; break; }
  }
  
  return false;
}

bool Is_New_Tail_Position(int x, int y, int size)
{
  for (int n = 0; size > n; n++) {
    if (
      x == bridge_data[n].x_pos &&
      y == bridge_data[n].y_pos
    ) {
      return false;
    }
  }
  
  return true;
}

int main()
{
  FILE *f = fopen("input.txt", "r");
  
  if (NULL == f) {
    exit(0);
  }
  
  char buffer[2000];
  
  bridge_data = malloc(10000 * 2 * sizeof(struct visited));
  
  facing face_dir = up;
  
  int head_pos_x = 0;
  int head_pos_y = 0;
  
  int tail_pos_x = 0;
  int tail_pos_y = 0;
  
  char move_delim[2];
  move_delim[0] = ' ';
  move_delim[1] = '\0';
  
  int visited_num = 0;
  
  while (NULL != fgets(buffer, 2000, f)) {
    if ('\n' != buffer[0]) {
      if (0 == visited_num) {
        bridge_data[0].x_pos = 0;
        bridge_data[0].y_pos = 0;
        
        visited_num++;
      }
      
      char *tmp_buffer = buffer;
      char *tmp = strtok(tmp_buffer, move_delim);
      
      char *str_dir = malloc(2);
      strncpy(str_dir, tmp, 1);
      
      tmp = strtok(NULL, move_delim);
      tmp[strlen(tmp) - 1] = '\0';
      
      int amount = 0;
      amount = atoi(tmp);
      
      if (0 == strcmp("U", str_dir)) {
        face_dir = up;
        
        while (0 < amount) {
          head_pos_y--;
          
          // Only move the tail if the head moves out of range by more than one tile.
          if (true == Tail_Should_Move(head_pos_x, head_pos_y, tail_pos_x, tail_pos_y, face_dir)) {
            if (tail_pos_x != head_pos_x) {
              tail_pos_x = head_pos_x;
            }
            
            tail_pos_y--;
            
            if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, visited_num)) {
              bridge_data[visited_num].x_pos = tail_pos_x;
              bridge_data[visited_num].y_pos = tail_pos_y;
              
              visited_num++;
            }
          }
          
          amount--;
        }
      } else if (0 == strcmp("R", str_dir)) {
        face_dir = right;
        
        while (0 < amount) {
          head_pos_x++;
          
          // Only move the tail if the head moves out of range by more than one tile.
          if (true == Tail_Should_Move(head_pos_x, head_pos_y, tail_pos_x, tail_pos_y, face_dir)) {
            if (tail_pos_y != head_pos_y) {
              tail_pos_y = head_pos_y;
            }
            
            tail_pos_x++;
            
            if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, visited_num)) {
              bridge_data[visited_num].x_pos = tail_pos_x;
              bridge_data[visited_num].y_pos = tail_pos_y;
              
              visited_num++;
            }
          }
          
          amount--;
        }
      } else if (0 == strcmp("D", str_dir)) {
        face_dir = down;
        
        while (0 < amount) {
          head_pos_y++;
          
          // Only move the tail if the head moves out of range by more than one tile.
          if (true == Tail_Should_Move(head_pos_x, head_pos_y, tail_pos_x, tail_pos_y, face_dir)) {
            if (tail_pos_x != head_pos_x) {
              tail_pos_x = head_pos_x;
            }
            
            tail_pos_y++;
            
            if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, visited_num)) {
              bridge_data[visited_num].x_pos = tail_pos_x;
              bridge_data[visited_num].y_pos = tail_pos_y;
              
              visited_num++;
            }
          }
          
          amount--;
        }
      } else if (0 == strcmp("L", str_dir)) {
        face_dir = left;
        
        while (0 < amount) {
          head_pos_x--;
          
          // Only move the tail if the head moves out of range by more than one tile.
          if (true == Tail_Should_Move(head_pos_x, head_pos_y, tail_pos_x, tail_pos_y, face_dir)) {
            if (tail_pos_y != head_pos_y) {
              tail_pos_y = head_pos_y;
            }
            
            tail_pos_x--;
            
            if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, visited_num)) {
              bridge_data[visited_num].x_pos = tail_pos_x;
              bridge_data[visited_num].y_pos = tail_pos_y;
              
              visited_num++;
            }
          }
          
          amount--;
        }
      } else {
        printf("Invalid direction provided.");
        exit(0);
      }
    }
  }
  
  printf("The number of positions that the tail of the rope visits at least once is %d.", visited_num);
  
  return 0;
}
