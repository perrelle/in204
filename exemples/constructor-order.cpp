#include <iostream>

void show_init(char const *name) {
    std::cout << "init " << name << std::endl;
}

class A {
public:
    A() {
        show_init("A");
    }
};

class P1 {
public:
    P1() {
        show_init("P1");
    }
};

class P2 {
public:
    P2() {
        show_init("P2");
    }
};

class B : public A { 
public:
    P1 p1;
    P2 p2;

    B() : p2(), A(), p1() {
        show_init("B");
    }
};

int main() {
    B b;
    return 0;
}
