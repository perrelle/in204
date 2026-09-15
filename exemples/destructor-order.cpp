#include <iostream>

void show_destruct(char const *name) {
    std::cout << "destruct " << name << std::endl;
}

class A {
public:
    ~A() {
        show_destruct("A");
    }
};

class P1 {
public:
    ~P1() {
        show_destruct("P1");
    }
};

class P2 {
public:
    ~P2() {
        show_destruct("P2");
    }
};

class B : public A { 
public:
    P1 p1;
    P2 p2;

    ~B() {
        show_destruct("B");
    }
};

int main() {
    B b;
    return 0;
}
