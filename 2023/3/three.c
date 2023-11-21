#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "three.h"

/*
 * Rather than using a switch statement and returning
 * before the break keyword, it seems better to
 * just use a series of if statements.
*/
int Get_Priority_Value(char ident)
{
  if ('a' == ident) {
    return 1;
  } else if ('b' == ident) {
    return 2;
  } else if ('c' == ident) {
    return 3;
  } else if ('d' == ident) {
    return 4;
  } else if ('e' == ident) {
    return 5;
  } else if ('f' == ident) {
    return 6;
  } else if ('g' == ident) {
    return 7;
  } else if ('h' == ident) {
    return 8;
  } else if ('i' == ident) {
    return 9;
  } else if ('j' == ident) {
    return 10;
  } else if ('k' == ident) {
    return 11;
  } else if ('l' == ident) {
    return 12;
  } else if ('m' == ident) {
    return 13;
  } else if ('n' == ident) {
    return 14;
  } else if ('o' == ident) {
    return 15;
  } else if ('p' == ident) {
    return 16;
  } else if ('q' == ident) {
    return 17;
  } else if ('r' == ident) {
    return 18;
  } else if ('s' == ident) {
    return 19;
  } else if ('t' == ident) {
    return 20;
  } else if ('u' == ident) {
    return 21;
  } else if ('v' == ident) {
    return 22;
  } else if ('w' == ident) {
    return 23;
  } else if ('x' == ident) {
    return 24;
  } else if ('y' == ident) {
    return 25;
  } else if ('z' == ident) {
    return 26;
  } else if ('A' == ident) {
    return 27;
  } else if ('B' == ident) {
    return 28;
  } else if ('C' == ident) {
    return 29;
  } else if ('D' == ident) {
    return 30;
  } else if ('E' == ident) {
    return 31;
  } else if ('F' == ident) {
    return 32;
  } else if ('G' == ident) {
    return 33;
  } else if ('H' == ident) {
    return 34;
  } else if ('I' == ident) {
    return 35;
  } else if ('J' == ident) {
    return 36;
  } else if ('K' == ident) {
    return 37;
  } else if ('L' == ident) {
    return 38;
  } else if ('M' == ident) {
    return 39;
  } else if ('N' == ident) {
    return 40;
  } else if ('O' == ident) {
    return 41;
  } else if ('P' == ident) {
    return 42;
  } else if ('Q' == ident) {
    return 43;
  } else if ('R' == ident) {
    return 44;
  } else if ('S' == ident) {
    return 45;
  } else if ('T' == ident) {
    return 46;
  } else if ('U' == ident) {
    return 47;
  } else if ('V' == ident) {
    return 48;
  } else if ('W' == ident) {
    return 49;
  } else if ('X' == ident) {
    return 50;
  } else if ('Y' == ident) {
    return 51;
  } else if ('Z' == ident) {
    return 52;
  }

  return 0;
}

int main()
{
  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  char buffer[300];
  // This needs to be a two-dimensional array to allow for multiple
  // lengths of different character strings but we over-allocate
  // memory to compensate for the variations in length.
  char buffer_copy[300][50];

  int sum = 0;
  int group_sum = 0;

  // Tracking when we need to group priorities.
  int group_ptr = 1;

  while (NULL != fgets(buffer, 300, f)) {
    // Accounting for the additional null-terminator.
    int buffer_size = strlen(buffer) - 1;
    // The value we'll use when looping through each half.
    int allocation = (buffer_size / 2);

    // The dynamic memory allocation is cruical to allow for
    // re-definition of char array lengths.
    char *first_compartment = malloc(allocation + 1);
    char *second_compartment = malloc(allocation + 1);

    // C doesn't support direct array modifications so instead we must
    // copy the content of one variable to it's new location.
    strcpy(buffer_copy[group_ptr - 1], buffer);

    int buffer_ptr = 0;
    // Tracking the for loop increments to tack the null-terminator
    // to the end of the compartment.
    int f_ptr = 0;
    int s_ptr = 0;

    for (f_ptr = 0; allocation > f_ptr; f_ptr++) {
      first_compartment[f_ptr] = buffer[buffer_ptr];
      buffer_ptr++;
    }

    for (s_ptr = 0; allocation > s_ptr; s_ptr++) {
      second_compartment[s_ptr] = buffer[buffer_ptr];
      buffer_ptr++;
    }

    f_ptr++;
    // The null-terminator is cruical to avoid unwanted behaviour
    // when dealing with these array lengths.
    first_compartment[f_ptr] = '\0';

    s_ptr++;
    second_compartment[s_ptr] = '\0';

    for (int f_count = 0; allocation > f_count; f_count++) {
      // We can just search the entire second compartment for the matching
      // character in the first without incrementing through both.
      if (NULL != strchr(second_compartment, first_compartment[f_count])) {
        char match;
        match = first_compartment[f_count];

        if ('*' != match) {
          sum += Get_Priority_Value(match);
        }

        break;
      }
    }

    if (0 == group_ptr % 3) {
      // Loop through the first rucksack to search for matches.
      for (int g = 0; (int) strlen(buffer_copy[group_ptr - 3]) > g; g++) {
        if (NULL != strchr(buffer_copy[group_ptr - 2], buffer_copy[group_ptr - 3][g])) {
          if (NULL != strchr(buffer_copy[group_ptr - 1], buffer_copy[group_ptr - 3][g])) {
            char group_match;

            group_match = buffer_copy[group_ptr - 3][g];
            group_sum += Get_Priority_Value(group_match);

            break;
          }
        }
      }
    }

    group_ptr++;
  }

  printf("The sum of the priorities of the item types is %d\n", sum);
  printf("The sum of the priorities for the badge groups is %d", group_sum);

  return 0;
}
