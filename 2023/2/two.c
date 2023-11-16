#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "two.h"

/*
 * strcmp requires a pointer to a sequence of characters that end
 * with a 0 so we can swap to using a direct char comparison
 * instead, with some so simple such as '=='.
 *
 * Also includes a new strategy guide based on the second column of the
 * input denoting whether the player should win, lose
 * or draw the match of rock, paper, scissors.
*/
int Get_Score(char opponent, char player, int ident)
{
  int score = 0;
  int secret_score = 0;

  if ('A' == opponent) {
    switch (player) {
      case 'X':
        score = 4;
        secret_score = 3;
        break;
      case 'Y':
        score = 8;
        secret_score = 4;
        break;
      case 'Z':
        score = 3;
        secret_score = 8;
        break;
    }
  } else if ('B' == opponent) {
    switch (player) {
      case 'X':
        score = 1;
        secret_score = 1;
        break;
      case 'Y':
        score = 5;
        secret_score = 5;
        break;
      case 'Z':
        score = 9;
        secret_score = 9;
        break;
    }
  } else if ('C' == opponent) {
    switch (player) {
      case 'X':
        score = 7;
        secret_score = 2;
        break;
      case 'Y':
        score = 2;
        secret_score = 6;
        break;
      case 'Z':
        score = 6;
        secret_score = 7;
        break;
    }
  }

  if (1 == ident) {
    return score;
  } else if (2 == ident) {
    return secret_score;
  }

  return 0;
}

int main()
{
  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  char buffer[2500];

  int total = 0;
  int secret_total = 0;

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

    total = total + Get_Score(c, p, 1);
    secret_total = secret_total + Get_Score(c, p, 2);
  }

  printf("The total rock, paper, scissors score based on the strategy guide is %d\n", total);
  printf("The total rock, paper, scissors score based on the top secret strategy guide is %d\n", secret_total);

  return 0;
}
