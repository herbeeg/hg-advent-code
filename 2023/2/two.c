#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "two.h"

/*
 * strcmp requires a pointer to a sequence of characters that end
 * with a 0 so we can swap to using a direct char comparison
 * instead, with some so simple such as '=='.
*/
int Get_Score(char opponent, char player)
{
  int score = 0;

  if ('A' == opponent) {
    if ('X' == player) {
      score = 4;
    } else if ('Y' == player) {
      score = 8;
    } else if ('Z' == player) {
      score = 3;
    }
  } else if ('B' == opponent) {
    if ('X' == player) {
      score = 1;
    } else if ('Y' == player) {
      score = 5;
    } else if ('Z' == player) {
      score = 9;
    }
  } else if ('C' == opponent) {
    if ('X' == player) {
      score = 7;
    } else if ('Y' == player) {
      score = 2;
    } else if ('Z' == player) {
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

    total = total + Get_Score(c, p);
  }

  printf("The total rock, paper, scissors score based on the strategy guide is %d\n", total);

  return 0;
}
