#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  printf("Start Main.\n");

  FILE *f = fopen("input.txt", "r");

  if (f == NULL) {
    exit(0);
  }

  char buffer[2245];
  int current = 0;
  int max = 0;

  while (fgets(buffer, 2245, f) != NULL) {
    if (strcmp(buffer, "") == 0) {
      current = 0;
    } else {
      printf("%s", buffer);
    }
  }
}
