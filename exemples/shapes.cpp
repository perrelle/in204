#include <iostream>

struct Point {
  float x;
  float y;

  Point() : x(0), y(0) {};
  Point(float x, float y) : x(x), y(y) {}

  void translate(Point vector) {
    x += vector.x;
    y += vector.y;
  }
};

class Shape {
private:
  Point center;

public:
  Shape(Point center) : center(center) {}

  void translate(Point vector) {
    center.translate(vector);
  }
};

class Circle : public Shape {
private:
  float radius;

public:
  Circle(Point center, float radius) : Shape(center), radius(radius) {}

  float area() const {
    const float pi = 3.14159265f;
    return pi * radius * radius;
  }
};

class Square : public Shape {
private:
  float side;

public:
  Square(Point center, float side) : Shape(center), side(side) {}

  float area() const {
    return side * side;
  }
};

int main() {
  Square square(Point(0.0f,0.0f), 2.0f);
  Circle circle(Point(4.0f,2.0f), 2.0f);

  square.translate(Point(-1.0f,-1.0f));
  circle.translate(Point(1.0f,0.0f));

  std::cout << "Square area: " << square.area() << std::endl;
  std::cout << "Circle area: " << circle.area() << std::endl;

  return 0;
}
