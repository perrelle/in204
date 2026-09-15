#include <iostream>

class D {
public:
    D() {
        std::cout << "D() called" << std::endl;
    }
};

class C {
    D d;
public:
    // If any other constructor is declared, then the default constructor is
    // not generated

    // C(int x) {}
    // C(C& other) {}
    // C(int x, int y) {}
};

int main() {
    C x;
    C y = x;
    return 0;
}
