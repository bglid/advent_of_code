#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int invalid_sequence(uint64_t i) {
  char buff[32];
  uint32_t max_length = sizeof(buff);
  int n = snprintf(buff, max_length, "%lu", i);
  if (n > 0) {
    // getting divisible pairs
    for (int position = 1; position <= n; position++) {
      if (n % position != 0) {
        continue;
      }
      uint64_t digits = n / position;
      // continue if we can't match pairs
      if (digits < 2) {
        continue;
      }

      int flag = 1;
      for (uint64_t j = 1; j < digits; j++) {
        if (memcmp(buff, buff + j * position, (size_t)position) != 0) {
          flag = 0;
          break;
        }
      }
      if (flag) {
        return 1;
      }
    }
  }
  return 0;
}

uint64_t find_invalid(uint64_t begin, uint64_t end) {
  uint64_t res = 0;
  // iterate through begin -> end, inclusive
  for (uint64_t i = begin; i <= end; i++) {
    if (invalid_sequence(i)) {
      res += i;
    }
    if (i == end) {
      break;
    }
  }
  return res;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Please add input file for day");
    return 1;
  }

  // opening the file
  char *file_path = argv[1];
  FILE *fptr;
  fptr = fopen(file_path, "rb");
  if (fptr == NULL) {
    printf("Can't read file");
    exit(EXIT_FAILURE);
  }
  // file size and EOF
  size_t file_size;
  long off_end;
  int return_check;
  char *buff;
  uint64_t result = 0;

  // going to the eof
  return_check = fseek(fptr, 0L, SEEK_END);
  if (return_check != 0) {
    printf("fseek() failed in file %s at line # %d\n", __FILE__, __LINE__ - 2);
    fclose(fptr);
    return EXIT_FAILURE;
  }
  // getting last position in bytes
  off_end = ftell(fptr);
  if (off_end < 0) {
    return EXIT_FAILURE;
  }
  fseek(fptr, 0, SEEK_SET);

  // using off end to get size of file
  file_size = (size_t)off_end;

  // allocating a buffer to hold file
  buff = malloc(file_size);
  if (buff == NULL) {
    printf("failed to allocate to file...");
    fclose(fptr);
    return EXIT_FAILURE;
  }

  // rewind to start of file
  rewind(fptr);

  // use fread to read file into buff
  uintptr_t bytes_read = 0;
  do {
    // each first unwritten buff, size of value in buff, num objects, file
    bytes_read +=
        fread(bytes_read + buff, sizeof(*buff), file_size - bytes_read, fptr);
  } while (bytes_read != file_size);

  // iterate through entire file
  for (uintptr_t i = 0; i < file_size;) {
    // get begin
    uint64_t begin = 0;
    uint64_t end = 0;

    // check that curr buff is a digit
    while (i < file_size && '0' <= buff[i] && buff[i] <= '9') {
      // turn into int, moving position over by 10^n
      begin = 10 * begin + buff[i] - '0';
      i++;
    }
    // skip delim
    while (i < file_size && ('0' > buff[i] || buff[i] > '9')) {
      i++;
    }
    // get end
    while (i < file_size && '0' <= buff[i] && buff[i] <= '9') {
      // turn into int, moving position over by 10^n
      end = 10 * end + buff[i] - '0';
      i++;
    }
    assert(begin <= end);

    // check for ids after hitting ,
    result += find_invalid(begin, end);

    // continue to next digit
    while (i < file_size && ('0' > buff[i] || buff[i] > '9')) {
      i++;
    }
  }
  printf("Result of invalids! %lu\n", result);

  fclose(fptr);
  free(buff);

  return 0;
}
