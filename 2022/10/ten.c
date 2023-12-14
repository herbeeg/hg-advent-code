#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int passed_cycles[6];
int passed_ptr = 0;

long int Check_Cycles(int count, long int strength, long int reg)
{
  for (int p = 0; p < 6; p++) {
    if (count == passed_cycles[p]) {
      return strength;
    }
  }
  
  passed_cycles[passed_ptr] = count;
  passed_ptr++;
  
  printf("%li\n", strength);
  printf("%li\n", reg);
  
  return strength + (count * reg);
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
      
      current_cycle++;
    }
  }
  
  printf("The sum of the six signal strengths is %li", total_signal_strength);
  
  return 0;
}
