#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  char buffer[1110];
  char *directories;
  
  char command_delim[2];
  command_delim[0] = ' ';
  command_delim[1] = '\0';

  while (NULL != fgets(buffer, 1110, f)) {
    if ('\n' != buffer[0]) {
      if ('$' == buffer[0]) {
        char *tmp_buffer = buffer;
        char *tmp = strtok(tmp_buffer, command_delim);
        tmp = strtok(NULL, command_delim);
        
        if ('c' == tmp[0] && 'd' == tmp[1]) {
          // Preparing to change the directory.
          tmp = strtok(NULL, command_delim);
          
          if ('/' == tmp[0]) {
            // Setting root directory.
          } else if ('.' == tmp[0] && '.' == tmp[1]) {
            // Going back one directory.
          } else {
            // Changing to a child directory.
          }
          
          char next;
          
          do {
            
          } while ('\n' != next);
        } else if ('l' == tmp[0] && 's' == tmp[1]) {
          // List the current directory and it's contents.
        }
      }
    }
  }

  return 0;
}
