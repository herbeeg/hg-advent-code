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
  long max = 0;

  while (NULL != fgets(buffer, 2245, f)) {
    // If the next line is just a newline char, then
    // we want to reset the current sum and check
    // if it is the largest so far.
    if (0 == strcmp(buffer, "\n")) {
      if (max < current) {
        max = current;
      }

      current = 0;
    } else {
      // The length of the line, minus any
      // additional newline chars.
      int buffer_size = strlen(buffer);
      char stripped[] = "";

      int ptr;

      // Only store the valid chars in a new string.
      for (ptr = 0; ptr < buffer_size; ptr++) {
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

  printf("%ld", max);

  return 0;
}
