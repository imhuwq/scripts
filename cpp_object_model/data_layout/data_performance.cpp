#include <stdio.h>
#include <stdlib.h>
#include <chrono>

const static size_t TestIter = 100000000; // 一亿
const static size_t TestCount = 10;
#define GetCost(end, start) std::chrono::duration_cast<std::chrono::milliseconds>((end) - (start)).count()

int array[3];

class Plain1 {
public:
    int val1;
};

class Plain2 : public Plain1 {
public:
    int val2;
};

class Plain3 : public Plain2 {
public:
    int val3;
};

class VirtualPlain2 : public virtual Plain1 {
public:
    int val2;
};

class VirtualPlain3 : public virtual Plain2 {
public:
    int val3;
};

void TestArrayPerformance() {
    auto start = std::chrono::steady_clock::now();
    auto end = start;
    long cost = 0;
    for (size_t c = 0; c < TestCount; c++) {
        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < TestIter; i++) {
            array[0] = i;
            array[1] = i;
            array[2] = i;
        }
        end = std::chrono::steady_clock::now();
        cost += GetCost(end, start);
    }
    printf("%-15s%-15s:%d ms\n", "Array", "", cost / 10);
}

void TestPlain3Performance() {
    Plain3 plain3Obj;
    Plain3 *plain3 = &plain3Obj;
    auto start = std::chrono::steady_clock::now();
    auto end = start;
    long cost = 0;
    for (size_t c = 0; c < TestCount; c++) {
        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < TestIter; i++) {
            plain3->val1 = i;
            plain3->val2 = i;
            plain3->val3 = i;
        }
        end = std::chrono::steady_clock::now();
        cost += GetCost(end, start);
    }
    printf("%-15s%-15s:%d ms\n", "Plain3", "Pointer", cost / 10);
}

void TestVirtualPlain3Performance() {
    VirtualPlain3 virtualPlain3Obj;
    VirtualPlain3 *virtualPlain3 = &virtualPlain3Obj;
    auto start = std::chrono::steady_clock::now();
    auto end = start;
    long cost = 0;
    for (size_t c = 0; c < TestCount; c++) {
        start = std::chrono::steady_clock::now();
        for (size_t i = 0; i < TestIter; i++) {
            virtualPlain3->val1 = i;
            virtualPlain3->val2 = i;
            virtualPlain3->val3 = i;
        }
        end = std::chrono::steady_clock::now();
        cost += GetCost(end, start);
    }
    printf("%-15s%-15s:%d ms\n", "VirtualPlain3", "Pointer", cost / 10);
}

int main() {
    TestArrayPerformance();
    TestPlain3Performance();
    TestVirtualPlain3Performance();
}