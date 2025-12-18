#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int64_t battery_window(char *line, int64_t line_length) {
  // doing a sliding window approach
  int l = 0;
  int r = l + 1;
  int single = 0;
  int doub = 0;
  int64_t curr = 0;
  int64_t biggest = 0;

  if (r >= line_length) {
    printf("Error in reading right pointer: %d\n", r);
    exit(EXIT_FAILURE);
  }

  while (r < line_length) {
    // get digits with arithmetric manipultaion
    single = line[r] - '0';
    doub = line[l] - '0';
    // concatenating digits
    curr = doub * 10 + single;

    // comparing to current res, sliding window-esq
    if (curr >= biggest) {
      biggest = curr;
    }
    if (single > doub && r < line_length) {
      l = r;
    }

    if (r > line_length) {
      return biggest;
    }

    r++;
    // if (r % 5 == 0) {
    //   printf("Final values: \nL %d %d\nR %d %d\nCurr: %" PRId64 "\n", l,
    //   single,
    //          r, doub, curr);
    // }
  }
  return biggest;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Please add input file for day\n");
    return 1;
  }

  // opening the file
  char *file_path = argv[1];
  FILE *fptr;
  fptr = fopen(file_path, "rb");
  if (fptr == NULL) {
    printf("UNABLE TO OPEN FILE: %s", file_path);
    exit(EXIT_FAILURE);
  }

  // getting the line length
  // size_t file_size = 0;
  int64_t line_length = 0;
  int64_t ch;
  int64_t eof = 0;
  int64_t res = 0;

  while ((ch = fgetc(fptr)) != '\n') {
    line_length++;
  }

  // getting the file length
  // going to the eof
  eof = ftell(fptr);
  if (eof < 0) {
    return EXIT_FAILURE;
  }
  fseek(fptr, 0, SEEK_SET);

  // rewind to start of file
  rewind(fptr);

  printf("line length: %" PRId64 "\n", line_length);
  // allocating buffer for each line
  char *buff = calloc((size_t)line_length + 2, sizeof *buff);

  if (!buff) {
    exit(EXIT_FAILURE);
  }

  while (fgets(buff, line_length + 2, fptr) != NULL) {
    // getting line length
    int n = strlen(buff);
    // decrementing n for our window algo
    if (n && buff[n - 1] == '\n') {
      buff[n - 1] = '\0';
      n--;
    }
    // updating res with sliding window
    res += battery_window(buff, (int64_t)n);
  }

  printf("\nTotal joltage: %" PRId64 "\n", res);

  fclose(fptr);
  free(buff);
  return 0;
}
