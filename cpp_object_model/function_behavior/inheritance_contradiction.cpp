#include <stdio.h>
#include <stdlib.h>

class A {
public:
    int val;
};

class B {
public:
    int val;
};

class AB : public A, public B {
public:
    int val;
};

class BA : public B, public A {
public:
    int val;
};

class C : public AB, public BA {
public:
};

int main() {
    C c;
    c.val = 2;
}