#include <cassert>
#include <iostream>

class matrix {
  int width;
  int height;
  int *cells;

public:
  matrix(int width, int height, int value = 0);
  explicit matrix(int size);
  ~matrix();
  int get(int row, int col);
  void set(int row, int col, int value);
  void init(int value);
  void print();
};

matrix::matrix(int width, int height, int value) :
    cells(new int[width * height * sizeof(int)]),
    width(width),
    height(height)
{
  init(value);
}

matrix::matrix(int size) :
    cells(new int[size * size * sizeof(int)]),
    width(size),
    height(size)
{
  init(0);
}

matrix::~matrix() {
  delete [] cells;
}

int matrix::get(int row, int col) {
  assert(0 <= row && row < height);
  assert(0 <= col && col < width);
  return cells[row * width + col];
}

void matrix::set(int row, int col, int value) {
  assert(0 <= row && row < height);
  assert(0 <= col && col < width);
  cells[row * width + col] = value;
}

void matrix::init(int value) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      set(i, j, value);
    }
  }
}

void matrix::print() {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      std::cout.width(3);
      std::cout << get(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

int main(void) {
  matrix m(4, 4, 1); // Appelle le constructeur, garantie l'initialisation
  m.set(1, 1, 0);
  m.print();
  return 0; // Au retour, appel automatique du destructeur
}
