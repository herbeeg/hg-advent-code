#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE *f = fopen("input.txt", "r");

  // Terminate if file is invalid.
  if (NULL == f) {
    exit(0);
  }

  // Line storage.
  char buffer[2245];

  long current = 0;
  long top_three[3] = { 0, 0, 0 };

  while (NULL != fgets(buffer, 2245, f)) {
    // If the next line is just a newline char, then
    // we want to reset the current sum and check
    // if it is the largest so far.
    if (0 == strcmp(buffer, "\n")) {
      for (int pivot = 0; 3 > pivot; pivot++) {
        if (top_three[pivot] < current) {
          // Shift the top three values if the next total
          // is higher than any of the currently
          // stored values.
          switch (pivot) {
            case 0:
              top_three[2] = top_three[1];
              top_three[1] = top_three[pivot];
              top_three[pivot] = current;
              break;
            case 1:
              top_three[2] = top_three[pivot];
              top_three[pivot] = current;
              break;
            case 2:
              top_three[pivot] = current;
              break;
          }

          // Don't continue to overwrite existing totals.
          break;
        }
      }

      current = 0;
    } else {
      // The length of the line, minus any
      // additional newline chars.
      int buffer_size = strlen(buffer);
      char stripped[] = "";

      int ptr;

      // Only store the valid chars in a new string.
      for (ptr = 0; buffer_size > ptr; ptr++) {
        stripped[ptr] = buffer[ptr];
      }

      char *end;
      // Convert the character string to long so integers
      // can be added to the total and compared against
      // the existing maximum.
      long val = strtol(stripped, &end, 10);

      current = current + val;
    }
  }

  printf("The elf with the most calories is carrying %ld.\n", top_three[0]);
  printf("The elves with the three most calories are carrying %ld.\n", top_three[0] + top_three[1] + top_three[2]);

  return 0;
}
