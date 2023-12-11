#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nine.h"

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

bool Is_New_Tail_Position(int x, int y, Data d)
{
  return true;
}

int main()
{
  FILE *f = fopen("input.txt", "r");
  
  if (NULL == f) {
    exit(0);
  }
  
  char buffer[2000];
  
  struct bridge *bridge_data = malloc(2 * sizeof(struct bridge));
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
        struct visited *vis = malloc(2 * sizeof(struct visited));
        vis[0].id = 0;
        vis[0].x_pos = 0;
        vis[0].y_pos = 0;
        
        bridge_data[0].start_x = 0;
        bridge_data[0].start_y = 0;
        bridge_data[0].visited_ids[0] = *vis;
        
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
            
            if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, *bridge_data)) {
              struct visited *new_tail = malloc(2 * sizeof(struct visited));
              new_tail[0].id = visited_num;
              new_tail[0].x_pos = tail_pos_x;
              new_tail[0].y_pos = tail_pos_y;
              
              bridge_data[visited_num].visited_ids[visited_num] = *new_tail;
              
              printf("ok");
            }
          }
          
          amount--;
        }
      } else if (0 == strcmp("R", str_dir)) {
        face_dir = right;
      } else if (0 == strcmp("D", str_dir)) {
        face_dir = down;
      } else if (0 == strcmp("L", str_dir)) {
        face_dir = left;
      } else {
        printf("Invalid direction provided.");
        exit(0);
      }
    }
  }
  
  return 0;
}
