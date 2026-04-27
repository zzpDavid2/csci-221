#include "stl.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

uint32_t Tracer::head = 0;

Tracer::Tracer() : id(head++) {
    std::cout << "Tracer " << id << " created" << std::endl;
}

Tracer::Tracer(const Tracer &other) : id(head++) {
    std::cout << "Tracer " << id << " created by copying Tracer " << other.id << std::endl;
}

Tracer::~Tracer() {
    head--;
    std::cout << "Tracer " << id << " destroyed" << std::endl;
}

uint32_t Tracer::get_id() const { return id; }

void Tracer::operator=(const Tracer &other) {
    std::cout << "Tracer " << id << " set equal to Tracer " << other.id << std::endl;
}

bool Tracer::operator<(const Tracer &other) const {
    return id < other.id;
}

int main() {
    // (b): array of 16 Tracers
    cout << "Array of 16 Tracers:" << endl;
    Tracer tracers_array[16];

    // (c): STL vector of 16 Tracers
    cout << "STL vector of 16 Tracers:" << endl;
    std::vector<Tracer> tracers_vector(16);

    // (d): STL set of 16 Tracers
    cout << "STL set of 16 Tracers:" << endl;
    std::set<Tracer> tracers_set;
    for (int i = 0; i < 16; i++) {
        tracers_set.insert(Tracer());
    }

    // (e): STL sort on the vector
    cout << "STL sort on the vector of Tracers:" << endl;
    std::sort(tracers_vector.begin(), tracers_vector.end());

    // (f): STL set_union on two sets
    cout << "STL set_union on two sets of Tracers:" << endl;
    std::set<Tracer> tracers_set2;
    for (int i = 0; i < 2; i++) {
        tracers_set2.insert(Tracer());
    }
    std::set<Tracer> tracers_union;
    std::set_union(tracers_set.begin(), tracers_set.end(),
                   tracers_set2.begin(), tracers_set2.end(),
                   std::inserter(tracers_union, tracers_union.begin()));

    // (g): STL set of 16 unique_ptrs to Tracers
    cout << "STL set of 16 unique_ptrs to Tracers:" << endl;
    std::set<std::unique_ptr<Tracer>> tracer_ptr_set;
    for (int i = 0; i < 16; i++) {
        tracer_ptr_set.insert(std::make_unique<Tracer>());
    }

    // (h): STL set of 16 shared_ptrs to Tracers
    cout << "STL set of 16 shared_ptrs to Tracers:" << endl;
    std::set<std::shared_ptr<Tracer>> tracer_shared_ptr_set;
    for (int i = 0; i < 16; i++) {
        tracer_shared_ptr_set.insert(std::make_shared<Tracer>());
    }

    return 0;
}
