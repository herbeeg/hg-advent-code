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
  
  struct directory *directories = malloc(250 * 2 * sizeof(struct directory));
  struct file *files = malloc(500 * 2 * sizeof(struct file));
  
  int num_of_dirs = 0;
  int num_of_files = 0;
  
  // Directory strings.
  
  char root_dir[2];
  root_dir[0] = '/';
  root_dir[1] = '\0';
  
  char back_dir[3];
  back_dir[0] = '.';
  back_dir[1] = '.';
  back_dir[2] = '\0';
  
  // Command strings.
  
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
  
  // Misc strings.
  
  char command_delim[2];
  command_delim[0] = ' ';
  command_delim[1] = '\0';

  char *current_dir = malloc(32);
  
  int current_parent = 0;

  while (NULL != fgets(buffer, 1110, f)) {
    if ('\n' != buffer[0]) {
      if ('$' == buffer[0]) {
        char *tmp_buffer = buffer;
        char *tmp = strtok(tmp_buffer, command_delim);
        tmp = strtok(NULL, command_delim);

        if (0 == strncmp(tmp, cd_command, 2)) {
          // Preparing to change the directory.
          tmp = strtok(NULL, command_delim);
          
          // "cd /"
          if (0 == strncmp(tmp, root_dir, 1)) {
            // Setting root directory. We can set these as hard values
            // as we touch on the root dir once at the beginning.
            strcpy(directories[0].name, "root\0");
            directories[0].id = 0;
            directories[0].parent = -1;
            directories[0].num_of_children = 0;
            directories[0].local_size = 0;
            
            // Tracking the struct array ID of the current dir parent.
            current_parent = 0;
            strcpy(current_dir, "root\0");
            num_of_dirs++;
          // "cd .."
          } else if (0 == strncmp(tmp, back_dir, 2)) {
            // Going back one directory.
            for (int cd_dot_dot = 0; num_of_dirs > cd_dot_dot; cd_dot_dot++) {
              if (directories[cd_dot_dot].id == current_parent) {
                int parent_dir_id = directories[cd_dot_dot].parent;
                
                for (int parent_ch_ids = 0; directories[parent_dir_id].num_of_children > parent_ch_ids; parent_ch_ids++) {
                  if (directories[directories[parent_dir_id].child_ids[parent_ch_ids]].id == current_parent) {
                    current_parent = directories[directories[parent_dir_id].id].id;
                    strcpy(current_dir, directories[current_parent].name);
                  }
                }
              }
            }
          // "cd xx"
          } else {
            // Changing to a child directory.
            
            // We want to take off any newline characters so that string comparisons
            // later on will not experience any mismatches from literals to those
            // read from the buffer.
            char *ch_dup = strdup(tmp);
            ch_dup[strlen(ch_dup) - 1] = '\0';
            
            strcpy(current_dir, ch_dup);
            
            for (int cd_xx = 0; num_of_dirs > cd_xx; cd_xx++) {
              if (directories[cd_xx].id == current_parent) {
                for (int ch_ids = 0; directories[cd_xx].num_of_children > ch_ids; ch_ids++) {
                  // Since there is the potential for duplicate directory names, we check against
                  // both the directory's name and where said directory is include in the
                  // parent dir's list of children.
                  if (
                    0 == strcmp(directories[directories[cd_xx].child_ids[ch_ids]].name, current_dir) &&
                    directories[directories[cd_xx].child_ids[ch_ids]].parent == current_parent
                  ) {
                    current_parent = directories[directories[cd_xx].child_ids[ch_ids]].id;
                    strcpy(current_dir, directories[current_parent].name);
                  }
                }
              }
            }
          }
        } else if (0 == strncmp(tmp, ls_command, 2)) {
          // Do nothing, take stock.
        }
      } else {
        char *tmp_buffer = buffer;
        
        // "dir xx"
        if (0 == strncmp(tmp_buffer, dir_command, 3)){
          char *tmp = strtok(tmp_buffer, command_delim);
          tmp = strtok(NULL, command_delim);
          
          char *dup = strdup(tmp);
          dup[strlen(dup) - 1] = '\0';
          
          strcpy(directories[num_of_dirs].name, dup);
          directories[num_of_dirs].id = num_of_dirs;
          directories[num_of_dirs].parent = current_parent;
          
          for (int dir_ptr = 0; num_of_dirs > dir_ptr; dir_ptr++) {
            if (directories[dir_ptr].id == current_parent) {
              // Adding the directory to it's parent's list of child IDs.
              directories[dir_ptr].child_ids[directories[dir_ptr].num_of_children] = num_of_dirs;
              directories[dir_ptr].num_of_children += 1;
              num_of_dirs++;
              
              // We only want to add one child at a time.
              break;
            }
          }
        // "1234567890 xx[.yy]"
        } else {
          char *tmp = strtok(tmp_buffer, command_delim);
          char *cpy = strdup(tmp);
          // The file sizes get rather large, including the totals so we use
          // long integers to cover all bases.
          signed long long int file_size = atol(cpy);
          
          files[num_of_files].id = num_of_files;
          files[num_of_files].parent = current_parent;
          
          for (int dir_f_ptr = 0; num_of_dirs > dir_f_ptr; dir_f_ptr++) {
            if (directories[dir_f_ptr].id == current_parent) {
              // Add the file sizes to the parent directory as a starter before we
              // traverse the tree later to sum all of the sizes.
              directories[dir_f_ptr].local_size += file_size;
              num_of_files++;
              
              break;
            }
          }
        }
      }
    }
  }
  
  for (int d = 0; num_of_dirs > d; d++) {
    int parent_ident = directories[d].parent;
    
    while (0 <= parent_ident) {
      // Ensure that we count back through the directories to increase
      // the total sizes past just the initial parent.
      directories[parent_ident].local_size += directories[d].local_size;
      parent_ident = directories[parent_ident].parent;
    }
  }
  
  signed long long int dir_sum = 0;
  
  for (int ds = 0; num_of_dirs > ds; ds++) {
    signed long long int size = directories[ds].local_size;
    
    if (
      0 <= size &&
      100000 >= size
    ) {
      dir_sum += size;
    }
  }
  
  signed long long int used_space = directories[0].local_size;
  signed long long int total_space = 70000000;
  signed long long int required_space = 30000000;
  
  signed long long int space_to_free = used_space + required_space - total_space;
  signed long long int current_smallest = 0;
  
  for (int d_free = 0; num_of_dirs > d_free; d_free++) {
    signed long long int size_to_compare = directories[d_free].local_size;
    
    if (0 == current_smallest) {
      current_smallest = size_to_compare;
    } else {
      if (
        space_to_free < size_to_compare &&
        current_smallest > size_to_compare
      ) {
        current_smallest = size_to_compare;
      }
    }
  }

  printf("The total size of the directories under 100,000 is %lli\n", dir_sum);
  printf("The smallest directory that would free up enough space is %lli large", current_smallest);

  return 0;
}
