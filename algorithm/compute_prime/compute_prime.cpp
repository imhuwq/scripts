#include <malloc.h>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

uint8_t *generate_bit_map(size_t length) {
    size_t bytes_count = length / 8;
    if (length % 8 != 0) bytes_count += 1;
    uint8_t *bit_map = (uint8_t *) malloc(bytes_count);

    for (int i = 0; i < bytes_count; i++) {
        *(bit_map + i) = 0xff;
    }

    return bit_map;
}

inline
void set_bit_pos(uint8_t *bit_map, size_t pos) {
    size_t byte_pos = pos / 8;
    size_t bit_pos = pos % 8;
    uint8_t mask = 0 | (1 << bit_pos);
    *(bit_map + byte_pos) |= mask;
}

inline
void unset_bit_pos(uint8_t *bit_map, size_t pos) {
    size_t byte_pos = pos / 8;
    size_t bit_pos = pos % 8;
    uint8_t mask = ~(0 | (1 << bit_pos));
    *(bit_map + byte_pos) &= mask;
}

inline
bool check_bit_pos(uint8_t *bit_map, size_t pos) {
    size_t byte_pos = pos / 8;
    size_t bit_pos = pos % 8;
    uint8_t mask = 0 | (1 << bit_pos);
    return (*(bit_map + byte_pos) & mask) != 0;
}

vector<uint32_t> compute_prime_bit_map(uint32_t roof) {
    vector<uint32_t> results;
    if (roof <= 1) return results;

    uint8_t *bit_map = generate_bit_map(roof);
    for (size_t i = 2; i < roof + 1; i++) {
        if (!check_bit_pos(bit_map, i)) continue;

        results.push_back(i);

        size_t multi = i + i;
        while (multi <= roof) {
            unset_bit_pos(bit_map, multi);
            multi += i;
        }
    }

    free(bit_map);
    return results;
}

uint8_t *generate_byte_map(size_t length) {
    uint8_t *byte_map = (uint8_t *) malloc(length);
    for (size_t i = 0; i < length; i++) {
        *(byte_map + i) = 0xff;
    }
    return byte_map;
}

vector<uint32_t> compute_prime_byte_map(uint32_t roof) {
    vector<uint32_t> results;
    if (roof <= 1) return results;

    uint8_t *byte_map = generate_byte_map(roof);
    for (size_t i = 2; i < roof + 1; i++) {
        if (byte_map[i] != 0xff) continue;

        results.push_back(i);

        size_t multi = i + i;
        while (multi <= roof) {
            byte_map[multi] = 0x00;
            multi += i;
        }
    }

    return results;
}

vector<uint32_t> compute_prime_vector_map(uint32_t roof) {
    vector<uint32_t> results;
    if (roof <= 1) return results;

    vector<bool> bool_map(roof, true);
    for (size_t i = 2; i < roof + 1; i++) {
        if (!bool_map[i]) continue;

        results.push_back(i);

        size_t multi = i + i;
        while (multi <= roof) {
            bool_map[multi] = false;
            multi += i;
        }
    }

    return results;
}

int main() {
    size_t prime_count = 100000000;

    cout << "Time cost of compute_prime_bit_map: " << endl;
    auto start = chrono::steady_clock::now();
    vector<uint32_t> p = compute_prime_bit_map(prime_count);
    auto finish = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(finish - start).count() << " ms" << endl;
    cout << chrono::duration_cast<chrono::seconds>(finish - start).count() << " s" << endl;
    cout << "\n======================\n" << endl;

    cout << "Time cost of compute_prime_byte_map: " << endl;
    start = chrono::steady_clock::now();
    vector<uint32_t> p2 = compute_prime_byte_map(prime_count);
    finish = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(finish - start).count() << " ms" << endl;
    cout << chrono::duration_cast<chrono::seconds>(finish - start).count() << " s" << endl;
    cout << "\n======================\n" << endl;

    cout << "Time cost of compute_prime_vector_map: " << endl;
    start = chrono::steady_clock::now();
    vector<uint32_t> p3 = compute_prime_vector_map(prime_count);
    finish = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::microseconds>(finish - start).count() << " ms" << endl;
    cout << chrono::duration_cast<chrono::seconds>(finish - start).count() << " s" << endl;
    cout << "\n======================\n" << endl;

    cout << boolalpha << "(p == p2): " << (p == p2) << ", size of p2: " << p.size() << endl;
    cout << boolalpha << "(p == p3): " << (p == p3) << ", size of p3: " << p.size() << endl;

    return 0;
}