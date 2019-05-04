#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

class C1 {
public:
    int val;
    char bit1;

    static void DisplayLayout(C1 *obj) {
        PRINT_START(C1);
        PRINT_OFFSET("C1", obj, &obj->val);
        PRINT_OFFSET("C1", obj, &obj->bit1);
        PRINT_END();
    }
};

class C2 : public C1 {
public:
    char bit2;

    static void DisplayLayout(C2 *obj) {
        PRINT_START(C2);
        PRINT_OFFSET("C1", obj, &obj->val);
        PRINT_OFFSET("C1", obj, &obj->bit1);
        PRINT_OFFSET("C2", obj, &obj->bit2);
        PRINT_END();
    }
};

class C3 : public C2 {
public:
    char bit3;

    static void DisplayLayout(C3 *obj) {
        PRINT_START(C3);
        PRINT_OFFSET("C1", obj, &obj->val);
        PRINT_OFFSET("C1", obj, &obj->bit1);
        PRINT_OFFSET("C2", obj, &obj->bit2);
        PRINT_OFFSET("C3", obj, &obj->bit3);
        PRINT_END();
    }
};


class C4 : public C3 {
public:
    char bit4;

    static void DisplayLayout(C4 *obj) {
        PRINT_START(C3);
        PRINT_OFFSET("C1", obj, &obj->val);
        PRINT_OFFSET("C1", obj, &obj->bit1);
        PRINT_OFFSET("C2", obj, &obj->bit2);
        PRINT_OFFSET("C3", obj, &obj->bit3);
        PRINT_OFFSET("C4", obj, &obj->bit4);
        PRINT_END();
    }
};


class CA {
public:
    char bitA;
};

class C1A: public C1, public CA {
public:
    char bit1A;

    static void DisplayLayout(C1A *obj) {
        PRINT_START(C1A);
        PRINT_OFFSET("C1", obj, &obj->val);
        PRINT_OFFSET("C1", obj, &obj->bit1);
        PRINT_OFFSET("CA", obj, &obj->bitA);
        PRINT_OFFSET("C1A", obj, &obj->bit1A);
        PRINT_END();
    }
};

int main() {
    C1 c1;
    C1::DisplayLayout(&c1);

    C2 c2;
    C2::DisplayLayout(&c2);

    C3 c3;
    C3::DisplayLayout(&c3);

    C4 c4;
    C4::DisplayLayout(&c4);

    C1A c1a;
    C1A::DisplayLayout(&c1a);
}
