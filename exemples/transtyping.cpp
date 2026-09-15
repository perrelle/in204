class A {
public:
    void f() {}
};

class B : public A {
public:
    void g() {}
};

class C : public B {};

void call_f(A* a) {
    a->f();
}

int main() {
    A a;
    B b;
    call_f(dynamic_cast<C*>(&b));
    return 0;
}
