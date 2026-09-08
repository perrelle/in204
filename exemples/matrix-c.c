#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct matrix {
  int width;
  int height;
  int *cells;
};

struct matrix matrix_create(int width, int height, int value);
void matrix_destroy(struct matrix *m);
int matrix_get(struct matrix *m, int row, int col);
void matrix_set(struct matrix *m, int row, int col, int value);
void matrix_init(struct matrix *m, int value);
void matrix_print(struct matrix *m);

struct matrix matrix_create(int width, int height, int value) {
  int *cells = malloc(width * height * sizeof(int));
  struct matrix m = { width, height, cells };
  matrix_init(&m, value);
  return m;
}

void matrix_destroy(struct matrix *m) {
  free(m->cells);
  m->cells = NULL;
}

int matrix_get(struct matrix *m, int row, int col) {
  assert(0 <= row && row < m->height);
  assert(0 <= col && col < m->width);
  assert(m->cells != NULL);
  return m->cells[row * m->width + col];
}

void matrix_set(struct matrix *m, int row, int col, int value) {
  assert(0 <= row && row < m->height);
  assert(0 <= col && col < m->width);
  assert(m->cells != NULL);
  m->cells[row * m->width + col] = value;
}

void matrix_init(struct matrix *m, int value) {
  for (int i = 0; i < m->height; i++) {
    for (int j = 0; j < m->width; j++) {
      matrix_set(m, i, j, value);
    }
  }
}

void matrix_print(struct matrix *m) {
  for (int i = 0; i < m->height; i++) {
    for (int j = 0; j < m->width; j++) {
      printf("%3d ", matrix_get(m, i, j));
    }
    printf("\n");
  }
}

int main(void) {
  struct matrix m = matrix_create(4, 4, 1);
  matrix_set(&m, 1, 1, 0);
  matrix_print(&m);
  matrix_destroy(&m);
  return 0;
}
