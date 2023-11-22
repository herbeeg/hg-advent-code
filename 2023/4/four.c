#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Allowing for more 'traditional' true/false checks.
typedef enum { false, true } bool;

int main()
{
  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  char buffer[1000];

  char delim[2];
  delim[0] = ',';
  // Null-termination of string is important during the comparison.
  delim[1] = '\0';

  char elf_delim[2];
  elf_delim[0] = '-';
  elf_delim[1] = '\0';

  int overlaps = 0;
  int partial_overlaps = 0;

  while (NULL != fgets(buffer, 1000, f)) {
    if ('\n' != buffer[0]) {
      // Store a copy of the splitting of the string as the
      // strtok function modifies the original value.
      char *tmp = strtok(buffer, delim);
      char *first_elf = tmp;

      // Passing null to the function automatically moves to the
      // following occurence using the delimiter as the
      // pointer is preserved in memory.
      tmp = strtok(NULL, delim);

      char *second_elf = tmp;

      // Allowing the conversion of character strings to integers.
      int first_min_id = atoi(strtok(first_elf, elf_delim));
      int first_max_id = atoi(strtok(NULL, elf_delim));

      int second_min_id = atoi(strtok(second_elf, elf_delim));
      int second_max_id = atoi(strtok(NULL, elf_delim));

      // The custom type definition is a nice feature, allowing
      // for customisable types and values to emulate
      // features that might occur more often in
      // other languages.
      bool b = false;

      if (second_min_id <= first_min_id) {
        if (second_max_id >= first_max_id) {
          overlaps++;
          b = true;
        }
      }

      // If the second part of the first if statement doesn't
      // pass, then we still want to run the reverse.
      if (true != b) {
        if (first_min_id <= second_min_id) {
          if (first_max_id >= second_max_id) {
            overlaps++;
          }
        }
      }

      // We only need to use the minimum IDs during the comparison to confirm
      // any overlaps that may occur during the process instead.
      //
      // Could potentially condense this down to one if statement but for
      // the time being, it can stay as slightly more readable.
      if ((second_min_id <= first_min_id) && (second_max_id >= first_min_id)) {
        partial_overlaps++;
      } else if ((first_min_id <= second_min_id) && (first_max_id >= second_min_id)) {
        partial_overlaps++;
      }
    }
  }

  printf("The number of assignment pairs where one fully contains the other is %d\n", overlaps);
  printf("The number of assignment pairs where the ranges overlap is %d\n", partial_overlaps);

  return 0;
}
