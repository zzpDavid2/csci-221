// #include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <vector>
#include "hello_world.hpp"
using namespace std;

// 3(a):
void add_to_int(uint32_t *ptr, uint32_t value = 1) {
    if (ptr != nullptr) {
        *ptr += value;
    }
}

// 3(b) 3(c)
void add_to_int(uint32_t &ptr, uint32_t value = 1) {
    ptr += value;
}

// 4(a)
namespace Grading211{
    double Update(double a, double b) {
        if(a>b){
            return a;
        } else {
            return (a+b)/2;
        }
    }
}

// 4(b)
namespace object{
    uint32_t band = 0;
}

namespace music{
    uint32_t band = 1;
}

uint32_t ring_band() {
    return object::band + music::band;
}

// 5(a)
void print_int_a() {
    uint32_t value = 0;
    cin >> value;
    value += 1;
    cout << "Integer: " << value << endl;
}

// 5(b)
void print_int_b() {
    uint32_t value = 0;
    string inpput;
    cin >> inpput;
    value = stoi(inpput);
    value += 1;
    cout << "Value: " << to_string(value) << endl;
}

// 5(c)
void print_int_c() {
    string inpput;
    cin >> inpput;
    stringstream ss = stringstream(inpput);
    uint32_t value = 0;
    ss >> value;
    value += 1;
    stringstream ss_out;
    ss_out << value;
    string output = ss_out.str();
    cout << "Value: " << output << endl;
}

// 6(a)
// typedef struct CharacterCount {
//     string string;
//     uint32_t *counts;
// };

// 6(b)
void count_characters(const string &s, CharacterCount &cc) {
    for (size_t i = 0; i < cc.get_string().size(); i++) {
        for (char c : s) {
            if (c == cc.get_string()[i]) {
                *(cc[i]) += 1;
            }
        }
    }
}

// 6(f)
CharacterCount::CharacterCount() : s(""), counts(0, 0) {}

// 6(e)
CharacterCount::CharacterCount(string str) : s(str) {
    counts = std::vector<uint32_t>(str.size(), 0);
}

// 6(g)
CharacterCount::CharacterCount(const CharacterCount &other) : s(other.s), counts(other.counts) {}

// 6(h)
CharacterCount::~CharacterCount() {}

// 6(d) 6(i)
string CharacterCount::get_string() const {
    return s;
}
const std::vector<uint32_t>& CharacterCount::get_array() const {
    return counts;
}
void CharacterCount::set_string(string str) {
    s = str;
    counts = std::vector<uint32_t>(str.size(), 0);
}
void CharacterCount::set_array(const std::vector<uint32_t> &arr) {
    if (arr.size() == s.size()) {
        counts = arr;
        return;
    }
    throw invalid_argument("Array size must match string length");
}
uint32_t *CharacterCount::operator[](size_t index) {
    if (index < s.size()) {
        return &counts[index];
    }
    throw out_of_range("Index out of range");
}

int main (int, char **) {
    // 1(a)
    // printf("Hello, World!");

    // 1(b)
    cout << "Hello, World!" << endl;

    // 2(a)
    uint32_t *ptr = nullptr;
    if (ptr == nullptr) {
        cout << "ptr is null" << endl;
    } else {
        cout << "ptr is not null" << endl;
    }

    // 2(b)
    ptr = new uint32_t(42);
    cout << "integer: " << *ptr << endl;

    // 2(c)
    delete ptr;

    // 2(d)
    ptr = new uint32_t[17];

    // 2(e)
    delete[] ptr;

    // 3 test
    uint32_t x = 5;
    add_to_int(&x, 3);
    cout << "3(a) add_to_int(&x=5, 3): " << x << " (expected 8)" << endl;
    uint32_t y = 5;
    add_to_int(y, 3);
    cout << "3(b) add_to_int(y=5, 3): " << y << " (expected 8)" << endl;
    uint32_t z = 5;
    add_to_int(z);
    cout << "3(c) add_to_int(z=5): " << z << " (expected 6)" << endl;

    // 4 test
    cout << "4(a) Update(5, 3): " << Grading211::Update(5, 3) << " (expected 5)" << endl;
    cout << "4(a) Update(3, 5): " << Grading211::Update(3, 5) << " (expected 4)" << endl;
    cout << "4(b) ring_band(): " << ring_band() << " (expected 1)" << endl;

    // 5 test
    cout << "5(a): "; print_int_a();
    cout << "5(b): "; print_int_b();
    cout << "5(c): "; print_int_c();

    // 6 test
    CharacterCount cc("abcrst ");
    count_characters("test string", cc);
    cout << "6 counts for \"abcrst \": ";
    for (size_t i = 0; i < cc.get_string().size(); i++) {
        cout << cc.get_array()[i] << " ";
    }
    cout << "(expected 0 0 0 1 2 3 1)" << endl;

    return 0;
}
