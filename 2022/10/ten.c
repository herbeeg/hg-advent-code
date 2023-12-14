#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE *f = fopen("input.txt", "r");
  
  if (NULL == f) {
    exit(0);
  }
  
  char buffer[150];
  
  int register_x = 1;
  int cycle = 0;
  
  // The commands to be executed on the next cycle.
  int queue_next[50];
  // The queued commands to be deferred by two cycles.
  int queue_defer[50];
  
  char cycle_delim[2];
  cycle_delim[0] = ' ';
  cycle_delim[1] = '\n';
  
  while (NULL != fgets(buffer, 150, f)) {
    if ('\n' != buffer[0]) {
      char *tmp_buffer = buffer;
      
      if (0 == strncmp("noop", tmp_buffer, 4)) {
        // Execute any commands in the queue and skip to the next cycle.
      } else {
        // Prepare to add the next register command to the deferred queue and
        // continue to the next cycle as before.
      }
    }
  }
  
  return 0;
}
