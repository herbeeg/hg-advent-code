#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Get_Score(char *opponent, char *player)
{
  int score = 0;

  if (0 == strcmp(opponent, "A")) {
    if (0 == strcmp(player, "X")) {
      score = 4;
    } else if (0 == strcmp(player, "Y")) {
      score = 8;
    } else if (0 == strcmp(player, "Z")) {
      score = 3;
    }
  } else if (0 == strcmp(opponent, "B")) {
    if (0 == strcmp(player, "X")) {
      score = 1;
    } else if (0 == strcmp(player, "Y")) {
      score = 5;
    } else if (0 == strcmp(player, "Z")) {
      score = 9;
    }
  } else if (0 == strcmp(opponent, "C")) {
    if (0 == strcmp(player, "X")) {
      score = 7;
    } else if (0 == strcmp(player, "Y")) {
      score = 2;
    } else if (0 == strcmp(player, "Z")) {
      score = 6;
    }
  }

  return score;
}

int main()
{
  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  char buffer[2500];

  int total = 0;

  while (NULL != fgets(buffer, 2500, f)) {
    char c;
    char p;

    int buffer_size = strlen(buffer);

    for (int ptr = 0; buffer_size > ptr; ptr++) {
      if (0 == ptr) {
        c = buffer[ptr];
      } else if (2 == ptr) {
        p = buffer[ptr];
      }
    }

    total = total + Get_Score(&c, &p);
  }

  printf("The total rock, paper, scissors score based on the strategy guide is %d\n", total);

  return 0;
}
