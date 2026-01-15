#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int MAX_PAPER = 4;
static const int dirs[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1},
};

struct position {
  int32_t x;
  int32_t y;
};

struct position_buff {
  struct position *pos;
  int32_t count;
};

// Give back true if direction is valid.
bool check_coords(char **grid, size_t rows, size_t cols, size_t i, size_t j,
                  int d, char *out) {
  // get coordinates
  int ni = (int)i + dirs[d][0];
  int nj = (int)j + dirs[d][1];

  // bounds checking
  if (ni < 0 || nj < 0 || ni >= (int)rows || nj >= (int)cols) {
    return false;
  }

  *out = grid[ni][nj];
  return true;
}

// i = rows, j = cols
bool is_valid_roll(char **grid, size_t i, size_t j, size_t rows, size_t cols) {
  int32_t count = 0;
  char out_res;

  // 8 = num directions
  for (int k = 0; k < 8; k++) {
    if (check_coords(grid, rows, cols, i, j, k, &out_res) && out_res == '@') {
      count++;
    }
  }

  return count < MAX_PAPER;
}

// Destroy grid freeing elements then grid.
void destroy_grid(char **grid, size_t rows) {
  for (size_t i = 0; i < rows; i++) {
    free(grid[i]);
  }
  free(grid);
}

// allocate check and create position buff
struct position_buff *create_position_buff() {
  struct position_buff *pos_buff = malloc(sizeof(struct position_buff));

  if (pos_buff == NULL) {
    fprintf(stderr, "ERROR MALLOC POS BUFF");
    exit(EXIT_FAILURE);
  }
  pos_buff->pos = NULL;
  pos_buff->count = 0;

  return pos_buff;
}

// Free...
void destroy_position_buff()

    int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Need input file to run\n");
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
      fprintf(stderr, "error malloc row\n");
      exit(EXIT_FAILURE);
    }
    memcpy(row, line, len + 1);

    // realloc mem for dynamic grid
    char **tmp = realloc(grid, (rows + 1) * sizeof(*grid));
    if (tmp == NULL) {
      fprintf(stderr, "error realloc\n");
      exit(EXIT_FAILURE);
    }

    grid = tmp;
    grid[rows++] = row;
  }

  int32_t count = 0;
  // part 2: continue until no more marks
  // being conservative that EVERY thing can be removed edge case
  struct position *position_buff =
      malloc(sizeof(struct position) * (rows * cols));
  do {
    int32_t rolls_to_delete = 0;
    // getting forklift counts
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        if (grid[i][j] == '@') {
          count += is_valid_roll(grid, i, j, rows, cols);
        }
      }
    }
  } while (rolls_to_delete > 0);

  printf("Found %d rolls...\n", count);
  fclose(fptr);

  free(position_buff);
  destroy_grid(grid, rows);

  return 0;
}
