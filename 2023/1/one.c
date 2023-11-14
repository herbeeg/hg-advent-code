#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  printf("Start Main.\n");

  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  char buffer[2245];
  long current = 0;
  long max = 0;

  while (NULL != fgets(buffer, 2245, f)) {
    if (0 == strcmp(buffer, "\n")) {
      if (max < current) {
        max = current;
      }

      current = 0;
    } else {
      int buffer_size = strlen(buffer);
      char stripped[] = "";

      int ptr;

      for (ptr = 0; ptr < buffer_size; ptr++) {
        stripped[ptr] = buffer[ptr];
      }

      char *end;
      long val = strtol(stripped, &end, 10);

      current = current + val;
    }
  }

  printf("%ld", max);
}
