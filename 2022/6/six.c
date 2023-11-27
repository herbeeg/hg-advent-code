#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

int main()
{
  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  char buffer[4096];

  int start = 0;
  int end = 3;

  int marker = 0;

  while (NULL != fgets(buffer, 4096, f)) {
    if ('\n' != buffer[0]) {
      do {
        // I think it's more readable to just track what has been scanned
        // so that we don't have to do any unnecessary comparisons.

        // [0] --> [1] & [2] & [3]
        // [1] --> [2] & [3]
        // [2] --> [3]
        int scanned = 0;
        bool duplicates = false;

        for (int s = start; end > s; s++) {
          if (0 == scanned) {
            if (
              buffer[s + 1] == buffer[s] ||
              buffer[s + 2] == buffer[s] ||
              buffer[s + 3] == buffer[s]
            ) {
              duplicates = true;
              // We can break out early to move on to the next if
              // a duplicate character has already been found.
              break;
            }
          } else if (1 == scanned) {
            if (
              buffer[s + 1] == buffer[s] ||
              buffer[s + 2] == buffer[s]
            ) {
              duplicates = true;
              break;
            }
          } else if (2 == scanned) {
            if (buffer[s + 1] == buffer[s]) {
              duplicates = true;
              break;
            }
          }

          scanned++;
        }

        start++;
        end++;

        // Mark the last character's position to return as the solution.
        if (false == duplicates) {
          marker = end;
        }
      } while (0 == marker);
    }
  }

  printf("The number of characters that need to be processed before the first start-of-packet marker is detected is %d\n", marker);

  return 0;
}
