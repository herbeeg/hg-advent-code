#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "seven.h"

int main()
{
  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  char buffer[1110];
  struct directory *directories = malloc(1);
  struct file *files = malloc(1);
  int num_of_dirs = 0;
  int num_of_files = 0;
  
  char command_delim[2];
  command_delim[0] = ' ';
  command_delim[1] = '\0';
  
  mode read_mode = changing;

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
            directories[0].name = malloc(5);
            strcpy(directories[0].name, "root\0");
            directories[0].id = 0;
            directories[0].parent = 0;
            
            num_of_dirs++;
          } else if ('.' == tmp[0] && '.' == tmp[1]) {
            // Going back one directory.
          } else {
            // Changing to a child directory.
          }
          
          read_mode = changing;
        } else if ('l' == tmp[0] && 's' == tmp[1]) {
          read_mode = listing;
        }
      } else {
        char *tmp_buffer = buffer;
        
        if (
          'd' == tmp_buffer[0] && 
          'i' == tmp_buffer[1] && 
          'r' == tmp_buffer[2]
        ) {
          directories = realloc(directories, ((num_of_dirs + 1) * 2 * sizeof(struct directory)));
          
          char *tmp = strtok(tmp_buffer, command_delim);
          tmp = strtok(NULL, command_delim);
          
          directories[num_of_dirs].name = malloc((int) strlen(tmp));
          strcpy(directories[num_of_dirs].name, tmp);
          directories[num_of_dirs].id = num_of_dirs;
          
          num_of_dirs++;
        } else {
          char *tmp = strtok(tmp_buffer, command_delim);
          long int file_size = atoi(tmp);
          char *ptr;
          
          files[num_of_files].id = num_of_files;
          files[num_of_files].size = strtol(tmp, &ptr, 10);
        }
      }
    }
  }

  return 0;
}
