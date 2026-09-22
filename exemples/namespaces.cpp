#include <iostream>

namespace mynamespace {
    void f() {
        std::cout << "mynamespace::f()" << std::endl;
    }
}

namespace mynamespace2 {
    void f() {
        std::cout << "mynamespace2::f()" << std::endl;
    }
}

namespace mynamespace {
    void g() {
        f();
    }
}

using namespace std;

int main() {
    cout << endl;
    mynamespace::f();
    return 0;
}
