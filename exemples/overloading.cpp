#include <cmath>

// Overloading of function norm

int norm(int x) {
  return x >= 0 ? x : -x;
}

double norm(double x) {
  return x >= 0.0 ? x : -x;
}

double norm(double x, double y) {
  return sqrt(x * x + y * y);
}

int main(void) {
  norm(42); // call to norm(int)
  norm(3.14159); // call to norm(double)
  norm(42.0, 2.0); // call to norm(double, double)
}
