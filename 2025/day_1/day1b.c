// Part two
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

// struct for rotations
struct rotation {
  int32_t distance;
  char direction;
};

struct solution {
  uint32_t zeros;
  int32_t dial;
};

// function to count the number of lines in .txt
int countLines(FILE *fp) {
  char ch;
  int lineCount = 0;
  while ((ch = fgetc(fp)) != EOF) {
    if (ch == '\n') {
      lineCount++;
    }
  }
  return lineCount;
}
// function to return 1 if the dial hits 0
static void dialCheck(struct solution *s, struct rotation *r) {
  switch (r->direction) {
  case 'R':
    for (int i = 0; i < r->distance; i++) {
      // update dial for each turn
      s->dial++;
      // check for going above 99
      if (s->dial > 99) {
        s->dial = 0;
      }
      // adding for each pass
      if (s->dial == 0) {
        s->zeros++;
      }
    }
    break;
  case 'L':
    for (int i = 0; i < r->distance; i++) {
      // update dial for each turn
      s->dial--;
      // check for going below 0
      if (s->dial < 0) {
        s->dial = 99;
      }
      // adding for each pass
      if (s->dial == 0) {
        s->zeros++;
      }
    }
    break;
  }
}

int main(int argc, char *argv[]) {
  (void)argc;

  char *fpath = argv[1];
  FILE *fptr;

  int32_t lineCount = 0;
  fptr = fopen(fpath, "r");

  // defensive read check
  if (fptr == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  lineCount = countLines(fptr);
  size_t bufferSize = 128 * lineCount;
  // need to rewind filepointer since it's at EOF
  rewind(fptr);
  char *lines = calloc(lineCount, bufferSize);

  // init solution struct
  struct solution sol = {
      .zeros = 0,
      .dial = 50,
  };

  // getline test
  while (getline(&lines, &bufferSize, fptr) > 0) {
    // getting the rotation instructions
    // setting endptr for strol
    char *endptr;
    struct rotation r = {
        .direction = *lines,
        .distance = (int32_t)strtol(lines + 1, &endptr, 10),
    };
    dialCheck(&sol, &r);
  }

  fclose(fptr);
  free(lines);
  printf("Number of zeros: %u\n", sol.zeros);
  return 0;
}
