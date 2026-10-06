int main() {
    int x = 42;
    int *p = &x; // Basic pointer initialization
    int *q;      // Uninitialized pointers are valid
    int y = *p;  // Read the pointed memory
    *p = y + 1;  // Write to the pointed memory
    p = &y;      // Pointers can be updated
}

void f() {
    int t[10] = { 0 };
    int *p;
    // Two distinct syntaxes, same result
    p = &t[0];
    p = t;
    // Pointer arithmetic, again two distinct syntaxes
    int y;
    y = t[3];
    y = *(t + 3);
}

struct s {
    int field;
};

void g() {
    s x = { 42 };
    s *p = &x;
    int y;
    // Two distinct syntaxes, same result
    y = (*p).field;
    y = p->field;
}