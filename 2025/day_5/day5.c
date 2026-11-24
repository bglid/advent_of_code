#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool parse_int_range(char *start, char **end, int64_t *output, bool first_num) {
  errno = 0;
  intmax_t val = strtol(start, end, 10);

  if (first_num && **end != '-')
    return false;

  if (errno == ERANGE || *end == start || *output < INT_MIN ||
      *output > INT_MAX) {
    fprintf(stderr, "Invalid first int\n");
    return false;
  }

  if (!first_num && **end != '\n' && **end != '\0')
    return false;

  *output = (int64_t)val;
  return true;
}

int main(int argc, char *argv[]) {
  printf("day 5...\n");
  if (argc != 2) {
    printf("Need input file to run\n");
    exit(EXIT_FAILURE);
  }

  printf("%s\n", argv[1]);

  char *file_path = argv[1];
  FILE *fptr = fopen(file_path, "r");
  if (!fptr) {
    printf("ERROR OPENING FILE AT: %s\n", file_path);
    exit(EXIT_FAILURE);
  }

  // line var to hold each line
  char line[1024];

  while (fgets(line, sizeof(line), fptr)) {
    if (line[0] == '\n') {
      break;
    }
    char *end;

    char *start = line;
    int64_t first_output = 0;
    bool first_res = parse_int_range(start, &end, &first_output, true);
    if (!first_res) {
      continue;
    }

    start = end + 1;
    errno = 0;
    int64_t second_output = 0;
    bool second_res = parse_int_range(start, &end, &second_output, false);
    if (!second_res) {
      continue;
    }

    printf("%ld -> %ld\n", first_output, second_output);
  }

  while (fgets(line, sizeof(line), fptr)) {
    if (line[0] == '\n') {
      break;
    }
  }

  // Plan:
  // 1. create a hash table
  // 2. loop through each entry, parse into n1 n2
  // 2.a loop from n1 -> n2, adding as keys
  // 2.a* continue over anything seen
  // 2.b update outer loop index to n2
  // 3. Break at carriage return
  // 4. start another loop at next num.
  // 5. if in hash table, increment result
}
