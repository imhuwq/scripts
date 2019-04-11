#include <stdio.h>
#include <iostream>

using namespace std;

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    cout << x << endl;
    cout << &x << endl;
    unsigned char* ptr = reinterpret_cast<unsigned char*>(&x);
    show_bytes((byte_pointer) &x, sizeof(int));
    show_bytes(ptr, sizeof(int));

    printf(" %.2x", ptr);
    printf("\n");
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}


int main() {
    int ival = 100;
    float fval = (float)ival;
    int *pval = &ival;

    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}