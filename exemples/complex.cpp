#include <iostream>

class Complex {
  double x, y;

public:
  Complex() : x(0.0), y(0.0) {} // Default constructor
  Complex(double x) : x(x), y (0.0) {} // **Implicit** conversion constructor
  Complex(Complex &c) : x(c.x), y(c.y) {} // Copy constructor
  Complex(double x, double y) : x(x), y(y) {} // Regular constructor

  void print() {
    std::cout << x << " + " << y << "i";
  }

  Complex operator+(Complex const &right) const {
    return Complex(x + right.x, y + right.y);
  }

  Complex &operator+=(Complex const &right) {
    x += right.x;
    y += right.y;
    return *this;
  }
};

int main() {
  Complex c1 = 2.0; // Uses the conversion constructor
  Complex const i(0.0, 1.0); // Uses the overloaded operator +
  Complex c2 = c1 + i;
  c2.print();
  std::cout << std::endl;
}
