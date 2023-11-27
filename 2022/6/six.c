#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

int main(int argc, char **argv)
{
  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  char buffer[4096];

  int start = 0;
  int end = 3;

  // To alternate the string section to search for duplicates, the
  // size can be passed in after changing the search logic.
  if (NULL != argv[1]) {
    // While the length passed is the size, subtract one from this
    // to convert it to the end index.
    end = atoi(argv[1]) - 1;
  }

  int marker = 0;

  while (NULL != fgets(buffer, 4096, f)) {
    if ('\n' != buffer[0]) {
      do {
        bool duplicates = false;

        for (int s = start; end > s; s++) {
          // I think it's more readable to just track what has been scanned
          // so that we don't have to do any unnecessary comparisons.

          // [0] --> [1] & [2] & [3]
          // [1] --> [2] & [3]
          // [2] --> [3]
          int scanned = s;
          do {
            // We just instead need to look one step ahead of the current
            // scanning index until the end of the portion given.
            if (buffer[scanned + 1] == buffer[s]) {
              duplicates = true;
              break;
            }

            scanned++;
          } while (end > (scanned));
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
