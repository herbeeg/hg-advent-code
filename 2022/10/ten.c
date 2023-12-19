#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int passed_cycles[6];
int passed_ptr = 0;

char crt[6][41];

void Fill_CRT_Screen_With_Defaults(char matrix[6][41])
{
  char autofill[41];
  autofill[0] = '.';
  autofill[1] = '.';
  autofill[2] = '.';
  autofill[3] = '.';
  autofill[4] = '.';
  autofill[5] = '.';
  autofill[6] = '.';
  autofill[7] = '.';
  autofill[8] = '.';
  autofill[9] = '.';
  autofill[10] = '.';
  autofill[11] = '.';
  autofill[12] = '.';
  autofill[13] = '.';
  autofill[14] = '.';
  autofill[15] = '.';
  autofill[16] = '.';
  autofill[17] = '.';
  autofill[18] = '.';
  autofill[19] = '.';
  autofill[20] = '.';
  autofill[21] = '.';
  autofill[22] = '.';
  autofill[23] = '.';
  autofill[24] = '.';
  autofill[25] = '.';
  autofill[26] = '.';
  autofill[27] = '.';
  autofill[28] = '.';
  autofill[29] = '.';
  autofill[30] = '.';
  autofill[31] = '.';
  autofill[32] = '.';
  autofill[33] = '.';
  autofill[34] = '.';
  autofill[35] = '.';
  autofill[36] = '.';
  autofill[37] = '.';
  autofill[38] = '.';
  autofill[39] = '.';
  autofill[40] = '\n';

  for (int c = 0; 6 > c; c++) {
    strcpy(matrix[c], autofill);
  }
}

long int Check_Cycles(int count, long int strength, long int reg)
{
  for (int p = 0; p < 6; p++) {
    if (count == passed_cycles[p]) {
      return strength;
    }
  }
  
  passed_cycles[passed_ptr] = count;
  passed_ptr++;
  
  return strength + (count * reg);
}

void Draw_To_File(char matrix[6][41])
{
  FILE *f_out = fopen("output.txt", "w");
  
  if (NULL == f_out) {
    exit(0);
  }
  
  for (int m_row = 0; 6 > m_row; m_row++) {
    for (int m_col = 0; 41 > m_col; m_col++) {
      fprintf(f_out, "%c", matrix[m_row][m_col]);
    }
  }
  
  fclose(f_out);
}

int main()
{
  FILE *f = fopen("input.txt", "r");
  
  if (NULL == f) {
    exit(0);
  }
  
  char buffer[150];
  
  // Using the long int data type here to represent the register value
  // to defend against any moments that could arise from the total
  // exceeding or going below [-32,767, +32,767].
  long int register_x = 1;
  long int current_cycle = 1;
  long int total_signal_strength = 0;
  
  // Fill the CRT buffer with dots so that when we need to draw a sprite
  // to the simulated screen, we can just change it to a hash.
  Fill_CRT_Screen_With_Defaults(crt);
  
  char cycle_delim[2];
  cycle_delim[0] = ' ';
  cycle_delim[1] = '\0';
  
  while (NULL != fgets(buffer, 150, f)) {
    if ('\n' != buffer[0]) {
      char *tmp_buffer = buffer;
      long int register_change = 0;
      
      if (20 == current_cycle) {
        total_signal_strength = Check_Cycles(20, total_signal_strength, register_x);
      } else if (60 == current_cycle) {
        total_signal_strength = Check_Cycles(60, total_signal_strength, register_x);
      } else if (100 == current_cycle) {
        total_signal_strength = Check_Cycles(100, total_signal_strength, register_x);
      } else if (140 == current_cycle) {
        total_signal_strength = Check_Cycles(140, total_signal_strength, register_x);
      } else if (180 == current_cycle) {
        total_signal_strength = Check_Cycles(180, total_signal_strength, register_x);
      } else if (220 == current_cycle) {
        total_signal_strength = Check_Cycles(220, total_signal_strength, register_x);
      }
      
      if (1 <= current_cycle && 40 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[0][new_cycle - 1] = '#';
        }
      } else if (41 <= current_cycle && 80 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[1][new_cycle - 1] = '#';
        }
      } else if (81 <= current_cycle && 120 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[2][new_cycle - 1] = '#';
        }
      } else if (121 <= current_cycle && 160 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[3][new_cycle - 1] = '#';
        }
      } else if (161 <= current_cycle && 200 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[4][new_cycle - 1] = '#';
        }
      } else if (201 <= current_cycle && 240 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[5][new_cycle - 1] = '#';
        }
      }
      
      if (0 == strncmp("addx", tmp_buffer, 4)) {
        // Prepare to add the next register command to the deferred queue and
        // continue to the next cycle as before.
        tmp_buffer[strlen(tmp_buffer) - 1] = '\0';
        
        char *add_val = strtok(tmp_buffer, cycle_delim);
        add_val = strtok(NULL, cycle_delim);
        
        register_change = atol(add_val);
        
        current_cycle++;
      }
      
      if (20 == current_cycle) {
        total_signal_strength = Check_Cycles(20, total_signal_strength, register_x);
      } else if (60 == current_cycle) {
        total_signal_strength = Check_Cycles(60, total_signal_strength, register_x);
      } else if (100 == current_cycle) {
        total_signal_strength = Check_Cycles(100, total_signal_strength, register_x);
      } else if (140 == current_cycle) {
        total_signal_strength = Check_Cycles(140, total_signal_strength, register_x);
      } else if (180 == current_cycle) {
        total_signal_strength = Check_Cycles(180, total_signal_strength, register_x);
      } else if (220 == current_cycle) {
        total_signal_strength = Check_Cycles(220, total_signal_strength, register_x);
      }
      
      register_x += register_change;
      
      if (1 <= current_cycle && 40 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[0][new_cycle - 1] = '#';
        }
      } else if (41 <= current_cycle && 80 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[1][new_cycle - 1] = '#';
        }
      } else if (81 <= current_cycle && 120 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[2][new_cycle - 1] = '#';
        }
      } else if (121 <= current_cycle && 160 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[3][new_cycle - 1] = '#';
        }
      } else if (161 <= current_cycle && 200 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[4][new_cycle - 1] = '#';
        }
      } else if (201 <= current_cycle && 240 >= current_cycle) {
        int new_cycle = current_cycle % 40;
        if (0 == new_cycle) {
          new_cycle = 40;
        }
        if ((register_x - 1) <= new_cycle && (register_x + 1) >= new_cycle) {
          crt[5][new_cycle - 1] = '#';
        }
      }
      
      current_cycle++;
    }
  }
  
  Draw_To_File(crt);
  printf("The sum of the six signal strengths is %li", total_signal_strength);
  
  return 0;
}
