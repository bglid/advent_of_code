#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Need input file to run");
    exit(EXIT_FAILURE);
  }

  // reading in file
  char *file_path = argv[1];
  FILE *fptr = fopen(file_path, "rb");
  if (!fptr) {
    printf("error opening file: %s\n", file_path);
    exit(EXIT_FAILURE);
  }

  int64_t length = 0;
  int64_t lines = 0;
  int c;
  int n;

  // getting the length of a line
  while ((c = fgetc(fptr)) != '\n') {
    length++;
  }
  rewind(fptr);

  // getting the number of lines
  while ((c = fgetc(fptr)) != EOF) {
    if (c == '\n') {
      lines++;
    }
    n++;
  }
  rewind(fptr);
  char *buff = malloc(n * sizeof(char));
  // reading input into buffer
  fgets(buff, n, fptr);
  if (buff == NULL) {
    printf("Error reading in input");
    exit(EXIT_FAILURE);
  }

  int count = 0;
  int64_t pos = 0;
  // reading the input like a matrix
  for (int64_t i = 0; i < lines; i++) {
    for (int64_t j = 0; j < length; j++) {
      // printf("pos check: %ld\n", pos);
      // checking for a @
      if (buff[pos] != '@') {
        pos++;
        continue;
        // @ found
      } else if (buff[pos] == '@') {
        // char up;
        // char down;
        // char left;
        // char right;
        count++;
      }
      pos++;
    }
  }
  printf("Test: %d\n", count);
  printf("test2: %c\n", buff[9]);

  fclose(fptr);
  free(buff);
  return 0;
}
