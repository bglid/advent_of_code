#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int64_t battery_window(char *line) {
  // doing a sliding window approach
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

  // using off end to get size of file
  // file_size = (size_t)eof;
  // rewind to start of file
  rewind(fptr);

  printf("line length: %lu\n", line_length);
  // allocating buffer for each line
  char *buff = calloc(line_length, sizeof *buff);
  while (fgets(buff, line_length + 2, fptr) != NULL) {
    // print line if newline
    printf("Line: %s\n", buff);
    // updating res with sliding window
    res += battery_window(buff);
  }

  printf("Total joltage: %lu", res);

  fclose(fptr);
  free(buff);
  return 0;
}
