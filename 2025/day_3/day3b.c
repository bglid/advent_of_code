#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int64_t total_jolts(char *buff, int64_t line_length) {

  int jolt_index = 0;
  char res[12];
  int start = 0;

  printf("%lu", line_length);
  // iterate through the 12 possible digits
  for (int i = 0; i < 12; i++) {
    // iterate through remaining potential positions
    char max_num = '0';
    for (int j = start; j < line_length - 12 + i; j++) {
      // get max digit and position
      if (buff[j] > max_num) {
        max_num = buff[j];
        start = j;
      }
    }
    if (jolt_index > 12) {
      printf("Issue with indexing");
      exit(EXIT_FAILURE);
    }
    res[jolt_index] = max_num;
    jolt_index++;
    start++;
    // printf("max position: %d\n", start);
  }
  // update and create the resulting jolt num
  int64_t jolts = atol(res);
  printf("res: %" PRId64 "\n", jolts);
  return jolts;
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
    res += total_jolts(buff, (int64_t)n);
  }

  printf("\nTotal joltage: %" PRId64 "\n", res);

  fclose(fptr);
  free(buff);
  return 0;
}
