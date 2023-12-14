#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nine.h"

struct visited *bridge_data;
struct visited *extended_bridge_data;

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

bool Chain_Should_Move(int hX, int hY, int tX, int tY)
{
  // A stripped down version of the check to see if the original tail
  // should move as we always want to let the subsequent links in
  // the chain move in a diagonal direction when the first
  // link follows the head.
  if (
    (hY + 1) < tY ||
    hX > (tX + 1) ||
    hY > (tY + 1) ||
    (hX + 1) < tX
  ) {
    return true;
  }
  
  return false;
}

bool Is_New_Tail_Position(int x, int y, int size, int length)
{
  if (2 == length) {
    for (int n = 0; size > n; n++) {
      if (
        x == bridge_data[n].x_pos &&
        y == bridge_data[n].y_pos
      ) {
        return false;
      }
    }
  } else if (10 == length) {
    for (int n = 0; size > n; n++) {
      if (
        x == extended_bridge_data[n].x_pos &&
        y == extended_bridge_data[n].y_pos
      ) {
        return false;
      }
    }
  }
  
  return true;
}

int main(int argc, char **argv)
{
  FILE *f = fopen("input.txt", "r");
  
  if (NULL == f) {
    exit(0);
  }
  
  char buffer[2000];
  
  bridge_data = malloc(10000 * 2 * sizeof(struct visited));
  extended_bridge_data = malloc(10000 * 2 *sizeof(struct visited));
  
  facing face_dir = up;
  
  // Tracking all of the positions between the head and tail.
  int rope_pos_x[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int rope_pos_y[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int chain_length = 8;
  
  int head_pos_x = 0;
  int head_pos_y = 0;
  
  int tail_pos_x = 0;
  int tail_pos_y = 0;
  
  char move_delim[2];
  move_delim[0] = ' ';
  move_delim[1] = '\0';
  
  int visited_num = 0;
  int ext_visited_num = 0;
  
  while (NULL != fgets(buffer, 2000, f)) {
    if ('\n' != buffer[0]) {
      if (
        0 == visited_num &&
        0 == ext_visited_num
      ) {
        bridge_data[0].x_pos = 0;
        bridge_data[0].y_pos = 0;
        extended_bridge_data[0].x_pos = 0;
        extended_bridge_data[0].y_pos = 0;
        
        visited_num++;
        ext_visited_num++;
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
          
          if (10 == atoi(argv[1])) {
            int cL = 0;
          
            if (true == Tail_Should_Move(head_pos_x, head_pos_y, rope_pos_x[cL], rope_pos_y[cL], face_dir)) {
              if (rope_pos_x[cL] != head_pos_x) {
                rope_pos_x[cL] = head_pos_x;
              }
              
              rope_pos_y[cL]--;
            }
            
            // Checking whether each link between the head and tail of the rope should change position.
            while (cL < chain_length - 1) {
              if (true == Chain_Should_Move(rope_pos_x[cL], rope_pos_y[cL], rope_pos_x[cL + 1], rope_pos_y[cL + 1])) {
                if (rope_pos_x[cL + 1] < rope_pos_x[cL]) {
                  rope_pos_x[cL + 1]++;
                } else if (rope_pos_x[cL + 1] > rope_pos_x[cL]) {
                  rope_pos_x[cL + 1]--;
                }
                
                if (rope_pos_y[cL + 1] < rope_pos_y[cL]) {
                  rope_pos_y[cL + 1]++;
                } else if (rope_pos_y[cL + 1] > rope_pos_y[cL]) {
                  rope_pos_y[cL + 1]--;
                }
              }
              
              cL++;
            }
            // endwhile.
            
            if (true == Chain_Should_Move(rope_pos_x[cL], rope_pos_y[cL], tail_pos_x, tail_pos_y)) {
              if (tail_pos_x < rope_pos_x[cL]) {
                tail_pos_x++;
              } else if (tail_pos_x > rope_pos_x[cL]) {
                tail_pos_x--;
              }
              
              // Since the rope chains move in a modified snake-like fashion, there are times
              // where the tail needs to move in the opposite direction to where the head
              // is facing in order to follow the previous link in the chain.
              if (tail_pos_y < rope_pos_y[cL]) {
                tail_pos_y++;
              } else if (tail_pos_y > rope_pos_y[cL]) {
                tail_pos_y--;
              }
            }
            
            if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, ext_visited_num, 10)) {
              extended_bridge_data[ext_visited_num].x_pos = tail_pos_x;
              extended_bridge_data[ext_visited_num].y_pos = tail_pos_y;
              
              ext_visited_num++;
            }
          } else {
            // Only move the next link in the chain if the one before it 
            // moves out of range by more than one tile.
            if (true == Tail_Should_Move(head_pos_x, head_pos_y, tail_pos_x, tail_pos_y, face_dir)) {
              if (tail_pos_x != head_pos_x) {
                tail_pos_x = head_pos_x;
              }
              
              tail_pos_y--;
              
              if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, visited_num, 2)) {
                bridge_data[visited_num].x_pos = tail_pos_x;
                bridge_data[visited_num].y_pos = tail_pos_y;
                
                visited_num++;
              }
            }
          }
          
          amount--;
        }
      } else if (0 == strcmp("R", str_dir)) {
        face_dir = right;
        
        while (0 < amount) {
          head_pos_x++;
          
          if (10 == atoi(argv[1])) {
            int cL = 0;
          
            if (true == Tail_Should_Move(head_pos_x, head_pos_y, rope_pos_x[cL], rope_pos_y[cL], face_dir)) {
              if (rope_pos_y[cL] != head_pos_y) {
                rope_pos_y[cL] = head_pos_y;
              }
              
              rope_pos_x[cL]++;
            }
            
            // Checking whether each link between the head and tail of the rope should change position.
            while (cL < chain_length - 1) {
              if (true == Chain_Should_Move(rope_pos_x[cL], rope_pos_y[cL], rope_pos_x[cL + 1], rope_pos_y[cL + 1])) {
                if (rope_pos_y[cL + 1] < rope_pos_y[cL]) {
                  rope_pos_y[cL + 1]++;
                } else if (rope_pos_y[cL + 1] > rope_pos_y[cL]) {
                  rope_pos_y[cL + 1]--;
                }
                
                if (rope_pos_x[cL + 1] < rope_pos_x[cL]) {
                  rope_pos_x[cL + 1]++;
                } else if (rope_pos_x[cL + 1] > rope_pos_x[cL]) {
                  rope_pos_x[cL + 1]--;
                }
              }
              
              cL++;
            }
            // endwhile.
            
            if (true == Chain_Should_Move(rope_pos_x[cL], rope_pos_y[cL], tail_pos_x, tail_pos_y)) {
              if (tail_pos_y < rope_pos_y[cL]) {
                tail_pos_y++;
              } else if (tail_pos_y > rope_pos_y[cL]) {
                tail_pos_y--;
              }
              
              if (tail_pos_x < rope_pos_x[cL]) {
                tail_pos_x++;
              } else if (tail_pos_x > rope_pos_x[cL]) {
                tail_pos_x--;
              }
            }
            
            if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, ext_visited_num, 10)) {
              extended_bridge_data[ext_visited_num].x_pos = tail_pos_x;
              extended_bridge_data[ext_visited_num].y_pos = tail_pos_y;
              
              ext_visited_num++;
            }
          } else {
            if (true == Tail_Should_Move(head_pos_x, head_pos_y, tail_pos_x, tail_pos_y, face_dir)) {
              if (tail_pos_y != head_pos_y) {
                tail_pos_y = head_pos_y;
              }
              
              tail_pos_x++;
              
              if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, visited_num, 2)) {
                bridge_data[visited_num].x_pos = tail_pos_x;
                bridge_data[visited_num].y_pos = tail_pos_y;
                
                visited_num++;
              }
            }
          }
          
          amount--;
        }
      } else if (0 == strcmp("D", str_dir)) {
        face_dir = down;
        
        while (0 < amount) {
          head_pos_y++;
          
          if (10 == atoi(argv[1])) {
            int cL = 0;
          
            if (true == Tail_Should_Move(head_pos_x, head_pos_y, rope_pos_x[cL], rope_pos_y[cL], face_dir)) {
              if (rope_pos_x[cL] != head_pos_x) {
                rope_pos_x[cL] = head_pos_x;
              }
              
              rope_pos_y[cL]++;
            }
            
            // Checking whether each link between the head and tail of the rope should change position.
            while (cL < chain_length - 1) {
              if (true == Chain_Should_Move(rope_pos_x[cL], rope_pos_y[cL], rope_pos_x[cL + 1], rope_pos_y[cL + 1])) {
                if (rope_pos_x[cL + 1] < rope_pos_x[cL]) {
                  rope_pos_x[cL + 1]++;
                } else if (rope_pos_x[cL + 1] > rope_pos_x[cL]) {
                  rope_pos_x[cL + 1]--;
                }
                
                if (rope_pos_y[cL + 1] < rope_pos_y[cL]) {
                  rope_pos_y[cL + 1]++;
                } else if (rope_pos_y[cL + 1] > rope_pos_y[cL]) {
                  rope_pos_y[cL + 1]--;
                }
              }
              
              cL++;
            }
            // endwhile.
            
            if (true == Chain_Should_Move(rope_pos_x[cL], rope_pos_y[cL], tail_pos_x, tail_pos_y)) {
              if (tail_pos_x < rope_pos_x[cL]) {
                tail_pos_x++;
              } else if (tail_pos_x > rope_pos_x[cL]) {
                tail_pos_x--;
              }
              
              if (tail_pos_y < rope_pos_y[cL]) {
                tail_pos_y++;
              } else if (tail_pos_y > rope_pos_y[cL]) {
                tail_pos_y--;
              }
            }
            
            if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, ext_visited_num, 10)) {
              extended_bridge_data[ext_visited_num].x_pos = tail_pos_x;
              extended_bridge_data[ext_visited_num].y_pos = tail_pos_y;
              
              ext_visited_num++;
            }
          } else {
            if (true == Tail_Should_Move(head_pos_x, head_pos_y, tail_pos_x, tail_pos_y, face_dir)) {
              if (tail_pos_x != head_pos_x) {
                tail_pos_x = head_pos_x;
              }
              
              tail_pos_y++;
              
              if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, visited_num, 2)) {
                bridge_data[visited_num].x_pos = tail_pos_x;
                bridge_data[visited_num].y_pos = tail_pos_y;
                
                visited_num++;
              }
            }
          }
          
          amount--;
        }
      } else if (0 == strcmp("L", str_dir)) {
        face_dir = left;
        
        while (0 < amount) {
          head_pos_x--;
          
          if (10 == atoi(argv[1])) {
            int cL = 0;
          
            if (true == Tail_Should_Move(head_pos_x, head_pos_y, rope_pos_x[cL], rope_pos_y[cL], face_dir)) {
              if (rope_pos_y[cL] != head_pos_y) {
                rope_pos_y[cL] = head_pos_y;
              }
              
              rope_pos_x[cL]--;
            }
            
            // Checking whether each link between the head and tail of the rope should change position.
            while (cL < chain_length - 1) {
              if (true == Chain_Should_Move(rope_pos_x[cL], rope_pos_y[cL], rope_pos_x[cL + 1], rope_pos_y[cL + 1])) {
                if (rope_pos_y[cL + 1] < rope_pos_y[cL]) {
                  rope_pos_y[cL + 1]++;
                } else if (rope_pos_y[cL + 1] > rope_pos_y[cL]) {
                  rope_pos_y[cL + 1]--;
                }
                
                if (rope_pos_x[cL + 1] < rope_pos_x[cL]) {
                  rope_pos_x[cL + 1]++;
                } else if (rope_pos_x[cL + 1] > rope_pos_x[cL]) {
                  rope_pos_x[cL + 1]--;
                }
              }
              
              cL++;
            }
            // endwhile.
            
            if (true == Chain_Should_Move(rope_pos_x[cL], rope_pos_y[cL], tail_pos_x, tail_pos_y)) {
              if (tail_pos_y < rope_pos_y[cL]) {
                tail_pos_y++;
              } else if (tail_pos_y > rope_pos_y[cL]) {
                tail_pos_y--;
              }
              
              if (tail_pos_x < rope_pos_x[cL]) {
                tail_pos_x++;
              } else if (tail_pos_x > rope_pos_x[cL]) {
                tail_pos_x--;
              }
            }
            
            if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, ext_visited_num, 10)) {
              extended_bridge_data[ext_visited_num].x_pos = tail_pos_x;
              extended_bridge_data[ext_visited_num].y_pos = tail_pos_y;
              
              ext_visited_num++;
            }
          } else {
            if (true == Tail_Should_Move(head_pos_x, head_pos_y, tail_pos_x, tail_pos_y, face_dir)) {
              if (tail_pos_y != head_pos_y) {
                tail_pos_y = head_pos_y;
              }
              
              tail_pos_x--;
              
              if (true == Is_New_Tail_Position(tail_pos_x, tail_pos_y, visited_num, 2)) {
                bridge_data[visited_num].x_pos = tail_pos_x;
                bridge_data[visited_num].y_pos = tail_pos_y;
                
                visited_num++;
              }
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
  
  printf("The number of positions that the tail of the rope visits at least once is %d.\n", visited_num);
  printf("The number of positions that the tail of the rope of length 10 visits at least once is %d.", ext_visited_num);
  
  return 0;
}
