void f() {
    int x;
    int &r = x;  // Basic pointer initialization
    int &r2;     // Uninitialized references are forbidden
    int y = r;   // Read the referenced memory
    r = y + 1;   // Write to the referenced memory
    r = &y;      // References cannot be updated
}

struct s {
    int field;
};

void g() {
    s x;
    s &p = x;
    int y;
    y = p.field;
}
