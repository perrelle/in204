#include <iostream>

class A {
private:
  int private_property;
  void private_method() {}

protected:
  int protected_property;
  void protected_method() {}

public:
  int public_property;
  void public_method() {}

  // Inside the class everything can be accessed
  void f() {
    private_property = 0; // ✅
    protected_property = 0; // ✅
    public_property = 0; // ✅
    protected_method(); // ✅
    private_method(); // ✅
    public_method(); // ✅
  }
  
  // Nested classes are not common, but are considered a member of the
  // outer class and can access private properties and methods
  class NestedClass {
    void f(A* that) {
      that->private_property = 0; // ✅
      that->protected_property = 0; // ✅
      that->public_property = 0; // ✅
      that->protected_method(); // ✅
      that->private_method(); // ✅
      that->public_method(); // ✅
    }
  };
};

class PublicChild : public A {
public:
  // Inside a derived class, private fields cannot be accessed
  void f() {
      private_property = 0; // ❌
      protected_property = 0; // ✅
      public_property = 0; // ✅
      protected_method(); // ✅
      private_method(); // ❌
      public_method(); // ✅
  }
};

class ProtectedChild : protected A {};

class PrivateChild : private A {};

int main() {
  // Outside the class and outside a derived class, only public members
  // can be accessed
  A a;
  a.private_property = 0; // ❌
  a.protected_property = 0; // ❌
  a.public_property = 0; // ✅
  a.protected_method(); // ❌
  a.private_method(); // ❌
  a.public_method(); // ✅

  PublicChild b;
  b.private_property = 0; // ❌
  b.protected_property = 0; // ❌
  b.public_property = 0; // ✅
  b.protected_method(); // ❌
  b.private_method(); // ❌
  b.public_method(); // ✅

  // When the inheritance is protected or private, the inheritance cannot
  // be seen outside the class and then the fields cannot be accessed.
  ProtectedChild c;
  c.private_property = 0; // ❌
  c.protected_property = 0; // ❌
  c.public_property = 0; // ❌
  c.protected_method(); // ❌
  c.private_method(); // ❌
  c.public_method(); // ❌

  PrivateChild d;
  c.private_property = 0; // ❌
  c.protected_property = 0; // ❌
  c.public_property = 0; // ❌
  c.protected_method(); // ❌
  c.private_method(); // ❌
  c.public_method(); // ❌

  return 0;
}
