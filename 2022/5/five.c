#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false, true } bool;

int main()
{
  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  // It seems to be far more consistent if we fill the arrays
  // with default values before making any changes so we
  // can manage the null-terminators along with making
  // direct changes to the 2D array itself.
  char crate_matrix[56][10] = {
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'}
  };
  char buffer[512];
  char top_crates[10];

  int matrix_ptr = 0;
  // While not as extendable, we decide to just pluck the values
  // from specific array indexes instead based on the given
  // input which is deemed to be far more consistent
  // than searching for the next square bracket.
  const int indexes[9] = { 1, 5, 9, 13, 17, 21, 25, 29, 33 };

  char matrix_delim[2];
  matrix_delim[0] = '[';
  matrix_delim[1] = '\0';

  char move_delim[2];
  move_delim[0] = ' ';
  move_delim[1] = '\0';

  bool matrix_read = false;

  while (NULL != fgets(buffer, 512, f)) {
    // Skip empty rows.
    if ('\n' != buffer[0]) {
      if (false == matrix_read) {
        for (int c = 0; 9 > c; c++) {
          if (' ' != buffer[indexes[c]]) {
            crate_matrix[48 + matrix_ptr][c] = buffer[indexes[c]];
          }
        }

        // We only want to grab the raw data from the rows of crates.
        if (7 <= matrix_ptr) {
          matrix_read = true;
        } else {
          matrix_ptr++;
        }
      } else {
        // Skip any lines that start with whitespace.
        if (' ' != buffer[0]) {
          char *tmp_buffer = buffer;
          // Shift twice to get to the first numeric move command.
          char *tmp = strtok(tmp_buffer, move_delim);
          tmp = strtok(NULL, move_delim);

          int move_amount = atoi(tmp);

          tmp = strtok(NULL, move_delim);
          tmp = strtok(NULL, move_delim);

          int move_from = atoi(tmp);

          tmp = strtok(NULL, move_delim);
          tmp = strtok(NULL, move_delim);

          int move_to = atoi(tmp);

          int from_row = 0;
          int dest_row = 0;

          // Keep scanning until we hit the first alpha character in the matrix.
          do {
            from_row++;
          } while ('-' == crate_matrix[from_row][move_from - 1]);

          do {
            dest_row++;
          } while ('-' == crate_matrix[dest_row][move_to - 1]);

          for (int m = 1; move_amount >= m; m++) {
            // Put the upcoming crate into the row above the destination column.
            dest_row--;

            crate_matrix[dest_row][move_to - 1] = crate_matrix[from_row][move_from - 1];
            // Make sure we mark the source of the crate as empty.
            crate_matrix[from_row][move_from - 1] = '-';

            // Move down to the next row to get the next crate.
            from_row++;
          }
        }
      }
    }
  }

  for (int parse_ptr = 0; 9 > parse_ptr; parse_ptr++) {
    int parse_row = 0;

    // Re-scan the matrix for the first alpha match in the column.
    do {
      parse_row++;
    } while ('-' == crate_matrix[parse_row][parse_ptr]);

    // Concat the top crate to the string for displaying the results.
    top_crates[parse_ptr] = crate_matrix[parse_row][parse_ptr];
  }

  printf("The crates at the top of each stack are: %s", top_crates);

  return 0;
}
