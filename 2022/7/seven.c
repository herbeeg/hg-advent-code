#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "seven.h"

const char * Get_Outer_Directory_By_Name(char *name, struct directory *dirs, int length)
{
  for (int l = 0; length > l; l++) {
    if (0 == strcmp(dirs[l].name, name)) {
      int parent_id = dirs[l].parent;
      
      for (int p = 0; length > p; p++) {
        if (parent_id == dirs[p].id) {
          return dirs[p].name;
        }
      }
    }
  }
  
  return "\0";
}

int Get_Parent_ID(char *search, struct directory *dirs, int length)
{
  for (int s = 0; length > s; s++) {
    if (0 == strcmp(dirs[s].name, search)) {
      return dirs[s].id;
    }
  }
  
  return -1;
}

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
  
  char cd_command[3];
  cd_command[0] = 'c';
  cd_command[1] = 'd';
  cd_command[2] = '\0';
  
  char dir_command[4];
  dir_command[0] = 'd';
  dir_command[1] = 'i';
  dir_command[2] = 'r';
  dir_command[3] = '\0';
  
  char ls_command[3];
  ls_command[0] = 'l';
  ls_command[1] = 's';
  ls_command[2] = '\0';
  
  char back_dir[3];
  back_dir[0] = '.';
  back_dir[1] = '.';
  back_dir[2] = '\0';
  
  char root_dir[2];
  root_dir[0] = '/';
  root_dir[1] = '\0';
  
  mode read_mode = changing;
  char *previous_dir = malloc(32);
  char *current_dir = malloc(32);

  while (NULL != fgets(buffer, 1110, f)) {
    if ('\n' != buffer[0]) {
      if ('$' == buffer[0]) {
        char *tmp_buffer = buffer;
        char *tmp = strtok(tmp_buffer, command_delim);
        tmp = strtok(NULL, command_delim);

        if (0 == strncmp(tmp, cd_command, 2)) {
          // Preparing to change the directory.
          tmp = strtok(NULL, command_delim);
          
          if (0 == strncmp(tmp, root_dir, 1)) {
            // Setting root directory.
            directories[0].name = malloc(5);
            strcpy(directories[0].name, "root\0");
            directories[0].id = 0;
            directories[0].parent = 0;
            
            num_of_dirs++;
            current_dir = "root";
          } else if (0 == strncmp(tmp, back_dir, 2)) {
            // Going back one directory.
            previous_dir = current_dir;
            current_dir = strdup(Get_Outer_Directory_By_Name(current_dir, directories, num_of_dirs));
          } else {
            // Changing to a child directory.
            tmp[strlen(tmp) - 1] = '\0';
            previous_dir = current_dir;
            current_dir = strdup(tmp);
          }
          
          read_mode = changing;
        } else if (0 == strncmp(tmp, ls_command, 2)) {
          read_mode = listing;
        }
      } else {
        char *tmp_buffer = buffer;
        
        if (0 == strncmp(tmp_buffer, dir_command, 3)){
          directories = realloc(directories, ((num_of_dirs + 1) * 2 * sizeof(struct directory)));
          
          char *tmp = strtok(tmp_buffer, command_delim);
          tmp = strtok(NULL, command_delim);
          
          // We want to take off any newline characters so that string comparisons
          // later on will not experience any mismatches from literals to those
          // read from the buffer.
          tmp[strlen(tmp) - 1] = '\0';
          directories[num_of_dirs].name = malloc((int) strlen(tmp));
          strcpy(directories[num_of_dirs].name, tmp);
          directories[num_of_dirs].id = num_of_dirs;
          directories[num_of_dirs].parent = Get_Parent_ID(current_dir, directories, num_of_dirs);
          
          num_of_dirs++;
        } else {
          files = realloc(files, ((num_of_files + 1) * 2 * sizeof(struct file)));
          
          char *tmp = strtok(tmp_buffer, command_delim);
          long int file_size = atol(tmp);
          char *ptr;
          
          files[num_of_files].id = num_of_files;
          files[num_of_files].size = file_size;
          files[num_of_files].parent = Get_Parent_ID(current_dir, directories, num_of_dirs);
          
          num_of_files++;
        }
      }
    }
  }

  for (int l = 0; num_of_dirs > l; l++) {
    printf("%s", directories[l].name);
  }
  
  printf("\n\n");
  
  for (int m = 0; num_of_files > m; m++) {
    printf("%li", files[m].size);
  }

  return 0;
}
