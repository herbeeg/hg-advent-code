#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false, true } bool;

// It seems to be far more consistent if we fill the arrays
// with default values before making any changes so we
// can manage the null-terminators along with making
// direct changes to the 2D array itself.
char crate_matrix[56][10];

void Fill_Matrix_With_Defaults(char matrix[56][10])
{
  char autofill[10];
  autofill[0] = '-';
  autofill[1] = '-';
  autofill[2] = '-';
  autofill[3] = '-';
  autofill[4] = '-';
  autofill[5] = '-';
  autofill[6] = '-';
  autofill[7] = '-';
  autofill[8] = '-';
  autofill[9] = '\0';

  for (int c = 0; 56 > c; c++) {
    strcpy(matrix[c], autofill);
  }
}

/*
 * Usage: ./five.out [arg], where arg is either a random string or "batch" for the modified output.
 */
int main(int argc, char **argv)
{
  FILE *f = fopen("input.txt", "r");

  if (NULL == f) {
    exit(0);
  }

  char buffer[512];

  Fill_Matrix_With_Defaults(crate_matrix);
  char *top_crates = malloc(10);

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
        char *bfr = malloc(36);

        strcpy(bfr, buffer);

        for (int c = 0; 9 > c; c++) {
          if (' ' != buffer[indexes[c]]) {
            crate_matrix[48 + matrix_ptr][c] = bfr[indexes[c]];
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

          // While this may have resolved the issue with unwanted overwriting of the matrix
          // memory by just allowing a command-line argument to be passed so we don't
          // have to maintain two matrices, the issue still stands when attempting
          // to use a read value from the file buffer in two different ways.
          //
          // Many attempts were had using functions like strcpy, which only allows you
          // to copy a fully-modified string anyway, meaning that you would have to
          // make another copy, make the update and then copy it back into the
          // matrix.
          //
          // I will settle with this solution for now since at least some knowledge was
          // gained about passing command-line arguments.
          if (0 == strcmp("batch", argv[1])) {
            dest_row -= move_amount;

            for (int mA = 1; move_amount >= mA; mA++) {
              crate_matrix[dest_row][move_to - 1] = crate_matrix[from_row][move_from - 1];
              // Make sure we mark the source of the crate as empty.
              crate_matrix[from_row][move_from - 1] = '-';

              dest_row++;
              from_row++;
            }
          } else {
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

  // Add a null-terminator onto the end of each string before printing.
  top_crates[9] = '\0';

  printf("The crates at the top of each stack are: %s\n", top_crates);

  return 0;
}
