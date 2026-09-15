#include <iostream>

class A {
public:
  void f() {
    std::cout << "A::f()" << std::endl;
  }
};

class B : public A {
public:
  void f() {
    std::cout << "B::f()" << std::endl;
  }

  void f(int x) {
    std::cout << "B::f(int)" << std::endl; 
  }
};

int main() {
  A a;
  B b;
  a.f();
  b.f();
  b.A::f();
  b.f(1);
  return 0;
}