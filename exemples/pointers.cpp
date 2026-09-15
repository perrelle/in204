void f() {
    int x;
    int *p = &x; // Basic pointer initialization
    int *q;      // Uninitialized pointers are valid
    int y = *p;  // Read the pointed memory
    *p = y + 1;  // Write to the pointed memory
    p = &y;      // Pointers can be updated
}

void g() {
    int t[10];
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

void h() {
    s x;
    s *p = &x;
    int y;
    // Two distinct syntaxes, same result
    y = (*p).field;
    y = p->field;
}