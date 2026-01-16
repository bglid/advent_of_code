#include <assert.h>
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

// Node for a doubly linked list repping the position
struct node {
  struct node *next;
  struct node *prev;
  int32_t x;
  int32_t y;
};

struct position_list {
  struct node *head;
  struct node *tail;
  int32_t count;
};

// Destroy grid freeing elements then grid.
void destroy_grid(char **grid, size_t rows) {
  for (size_t i = 0; i < rows; i++) {
    free(grid[i]);
  }
  free(grid);
}

// Create node to hold position
// Caller owns node, not the list
struct node *create_node() {
  // allocate mem for the node struct
  struct node *n = malloc(sizeof(struct node));

  n->next = NULL;
  n->x = 0;
  n->y = 0;

  if (n == NULL) {
    printf("Out of memory when trying to allocate node\n");
    exit(EXIT_FAILURE);
  }
  return n;
}

// destroy node after setting next to NULL
void destroy_node(struct node *pnode) { free(pnode); }

// allocate check and create position buff
struct position_list *create_position_list() {
  struct position_list *pos_list = malloc(sizeof(struct position_list));

  if (pos_list == NULL) {
    fprintf(stderr, "ERROR MALLOC POS LIST");
    exit(EXIT_FAILURE);
  }
  pos_list->head = NULL;
  pos_list->tail = NULL;
  pos_list->count = 0;

  return pos_list;
}

// append list node to linked list
void append(struct position_list *plist, struct node *item) {
  plist->count++;
  if (plist->head == NULL) {
    plist->head = plist->tail = item;
    return;
  }
  if (plist->tail == NULL) {
    plist->tail = item;
    return;
  }

  item->prev = plist->tail;
  plist->tail->next = item;
  plist->tail = item;
  return;
}

// Remove list node by index
struct node *remove_at(struct position_list *plist, int index) {
  struct node *cur = plist->head;

  for (int i = 0; cur != NULL && i < plist->count; i++) {
    // remove this item
    if (i == index) {
      plist->count--;

      // cur is both head and tail
      if (plist->count <= 0) {
        plist->head = NULL;
        plist->tail = NULL;
        cur->prev = NULL;
        cur->next = NULL;
        return cur;
      }

      if (cur == plist->head) {
        plist->head = cur->next;
        // // have to adjust the previous
        plist->head->prev = NULL;
      } else if (cur == plist->tail) {
        plist->tail = cur->prev;
        plist->tail->next = NULL;
      } else {
        cur->next->prev = cur->prev;
        cur->prev->next = cur->next;
      }

      // get rid of cur
      cur->prev = NULL;
      cur->next = NULL;
      return cur;
    }
    cur = cur->next;
  }
  fprintf(stderr, "UNABLE TO REMOVE NODE IN LINKEDLIST WITH INDEX: %d\n",
          index);
  exit(EXIT_FAILURE);
}
struct node *get(struct position_list *plist, int index) {
  struct node *cur = plist->head;
  for (int i = 0; cur != NULL && i < plist->count; i++) {
    if (i == index) {
      return cur;
    }
    cur = cur->next;
  }
  fprintf(stderr, "UNABLE TO GET NODE IN LINKEDLIST WITH INDEX: %d\n", index);
  exit(EXIT_FAILURE);
}

// Free position buff
void destroy_position_list(struct position_list *position_list) {
  free(position_list);
}

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

// marks grid with x based off of node coords
void mark_rolls(char **grid, struct node *n) { grid[n->y][n->x] = 'x'; }

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

  // part 2: continue until no more marks
  // being conservative that EVERY thing can be removed edge case
  struct position_list *pos_list = create_position_list();
  int32_t rolls_to_delete = 0;
  int32_t total_count = 0;
  do {
    // getting forklift counts
    int32_t local_count = 0;
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        if (grid[i][j] == '@') {
          if (is_valid_roll(grid, i, j, rows, cols)) {
            // create new node with these coords
            local_count++;
            struct node *n = create_node();
            n->x = j;
            n->y = i;
            append(pos_list, n);
          }
        }
      }
    }
    // mark rolls, and update pos list to reset
    rolls_to_delete = pos_list->count;
    for (int32_t k = 0; k < rolls_to_delete; k++) {
      mark_rolls(grid, pos_list->head);
      // removing head to avoid traversing
      destroy_node(remove_at(pos_list, 0));
    }
    assert(pos_list->count == 0);
    total_count += local_count;
  } while (rolls_to_delete > 0);

  printf("Found %d rolls...\n", total_count);
  fclose(fptr);

  destroy_grid(grid, rows);

  return 0;
}
