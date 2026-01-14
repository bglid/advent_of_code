#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int MAX_PAPER = 4;

enum Direction {
  UP_LEFT,
  UP,
  UP_RIGHT,
  RIGHT,
  DOWN_RIGHT,
  DOWN,
  DOWN_LEFT,
  LEFT,
};

// Give back the char at that direction from the value in the grid.
char get_direction(char **grid, size_t i, size_t j, enum Direction d) {
  char res;
  switch (d) {
  case UP_LEFT:
    res = grid[i - 1][j - 1];
    break;
  case UP:
    res = grid[i - 1][j];
    break;
  case UP_RIGHT:
    res = grid[i - 1][j + 1];
    break;
  case RIGHT:
    res = grid[i][j + 1];
    break;
  case DOWN_RIGHT:
    res = grid[i + 1][j + 1];
    break;
  case DOWN:
    res = grid[i + 1][j];
    break;
  case DOWN_LEFT:
    res = grid[i + 1][j - 1];
    break;
  case LEFT:
    res = grid[i][j - 1];
    break;
  // bad dir
  default:
    printf("INVALID DIRECTION: grid[%zu][%zu]", i, j);
  }
  return res;
}

int32_t check_roll(char input) {
  if (input == '@') {
    return 1;
  }
  return 0;
}

// i = rows, j = cols
bool count_rolls(char **grid, size_t i, size_t j, size_t rows, size_t cols) {
  int32_t count = 0;
  // all the ups
  if (i > 0) {
    char up = get_direction(grid, i, j, UP);
    count += check_roll(up);
    if (j > 0) {
      char up_left = get_direction(grid, i, j, UP_LEFT);
      count += check_roll(up_left);
    }
    if (j < cols) {
      char up_right = get_direction(grid, i, j, UP_RIGHT);
      count += check_roll(up_right);
    }
  }
  // left and right
  if (j > 0) {
    char left = get_direction(grid, i, j, LEFT);
    count += check_roll(left);
  }
  if (j < cols) {
    char right = get_direction(grid, i, j, RIGHT);
    count += check_roll(right);
  }
  // all the downs
  if (i < rows) {
    char down = get_direction(grid, i, j, DOWN);
    count += check_roll(down);
    if (j > 0) {
      char down_left = get_direction(grid, i, j, DOWN_LEFT);
      count += check_roll(down_left);
    }
    if (j < cols) {
      char down_right = get_direction(grid, i, j, DOWN_RIGHT);
      count += check_roll(down_right);
    }
  }
  if (count < MAX_PAPER) {
    return true;
  }
  return false;
}

// Destroy grid freeing elements then grid.
void destroy_grid(char **grid, size_t rows) {
  for (size_t i = 0; i < rows; i++) {
    free(grid[i]);
  }
  free(grid);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Need input file to run");
    exit(EXIT_FAILURE);
  }

  // reading in file
  char *file_path = argv[1];
  FILE *fptr = fopen(file_path, "r");
  if (!fptr) {
    printf("error opening file: %s\n", file_path);
    exit(EXIT_FAILURE);
  }

  char **grid = NULL;
  size_t rows = 0;
  size_t cols = 0;
  char line[1024];

  while (fgets(line, sizeof(line), fptr)) {
    size_t len = strcspn(line, "\n");
    line[len] = '\0';

    if (cols == 0) {
      cols = len;
    }

    char *row = malloc(len + 1);
    if (row == NULL) {
      printf("error malloc row");
      exit(EXIT_FAILURE);
    }
    memcpy(row, line, len + 1);

    // realloc mem for dynamic grid
    char **tmp = realloc(grid, (rows + 1) * sizeof(*grid));
    if (tmp == NULL) {
      printf("error realloc");
      exit(EXIT_FAILURE);
    }

    grid = tmp;
    grid[rows++] = row;
  }

  int32_t count = 0;
  printf("rows: %zu\n\n", rows);
  // getting forklift counts
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (grid[i][j] == '@') {
        count += count_rolls(grid, i, j, rows - 1, cols);
      }
    }
  }

  printf("Found %d rolls...\n", count);
  fclose(fptr);

  destroy_grid(grid, rows);

  return 0;
}
