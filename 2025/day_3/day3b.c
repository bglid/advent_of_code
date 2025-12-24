#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// stack approach
int64_t total_jolts(const char *buff, size_t line_length, size_t k) {
  // chars to remove
  size_t to_remove = (k < line_length) ? (line_length - k) : 0;

  // init stack
  char *stack = malloc(line_length * sizeof(int));
  size_t top = 0;

  // pop and add in order
  for (size_t i = 0; i < line_length; i++) {
    char num = buff[i];
    // placing into the stack correctly
    while (top > 0 && to_remove > 0 && stack[top - 1] < num) {
      top--;
      to_remove--;
    }
    stack[top++] = num;
  }

  // build jolt number with k digits
  uint64_t jolts;
  size_t digits = (top < k) ? top : k;

  for (size_t j = 0; j < digits; j++) {
    jolts = jolts * 10 + (stack[j] - '0');
  }
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
    size_t n = strlen(buff);
    // decrementing n for our window algo
    if (n && buff[n - 1] == '\n') {
      buff[n - 1] = '\0';
      n--;
    }
    // updating res with sliding window
    res += total_jolts(buff, n, 12);
  }

  printf("\nTotal joltage: %" PRId64 "\n", res);

  fclose(fptr);
  free(buff);
  return 0;
}
