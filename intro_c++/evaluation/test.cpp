#include "sorted_lists.hpp"
#include "cars.hpp"
#include <cassert>
#include <iostream>
#include <cmath>

using namespace std;

const float EPS = 1e-4f;
bool near(float a, float b) { return fabs(a - b) < EPS; }

// ── SortedList ────────────────────────────────────────────────────────────────

void test_sorted_list() {
    cout << "SortedList" << endl;

    // (a) default constructor
    {
        SortedList sl;
        assert(sl.size() == 0);
        assert(sl.is_sorted_lexicographically());
        cout << "  (a) default constructor" << endl;
    }

    // (b) copy constructor
    {
        SortedList a;
        a.insert("banana");
        a.insert("apple");
        SortedList b(a);
        assert(b.size() == 2);
        assert(b.get_string(0) == "apple");
        assert(b.get_string(1) == "banana");
        cout << "  (b) copy constructor" << endl;
    }

    // (c) sort order constructor
    {
        SortedList sl(SortedList::SortOrder::LENGTH);
        assert(sl.size() == 0);
        assert(sl.is_sorted_by_length());
        cout << "  (c) sort order constructor" << endl;
    }

    // (d) insert lexicographic
    {
        SortedList sl;
        sl.insert("cherry");
        sl.insert("apple");
        sl.insert("banana");
        assert(sl.size() == 3);
        assert(sl.get_string(0) == "apple");
        assert(sl.get_string(1) == "banana");
        assert(sl.get_string(2) == "cherry");
        cout << "  (d) insert lexicographic" << endl;
    }

    // (d) insert by length
    {
        SortedList sl(SortedList::SortOrder::LENGTH);
        sl.insert("banana");  // 6
        sl.insert("hi");      // 2
        sl.insert("apple");   // 5
        assert(sl.size() == 3);
        assert(sl.get_string(0) == "hi");
        assert(sl.get_string(1) == "apple");
        assert(sl.get_string(2) == "banana");
        cout << "  (d) insert by length" << endl;
    }

    // (e) remove middle
    {
        SortedList sl;
        sl.insert("apple");
        sl.insert("banana");
        sl.insert("cherry");
        sl.remove("banana");
        assert(sl.size() == 2);
        assert(sl.get_string(0) == "apple");
        assert(sl.get_string(1) == "cherry");
        cout << "  (e) remove middle" << endl;
    }

    // (e) remove head
    {
        SortedList sl;
        sl.insert("apple");
        sl.insert("banana");
        sl.remove("apple");
        assert(sl.size() == 1);
        assert(sl.get_string(0) == "banana");
        cout << "  (e) remove head" << endl;
    }

    // (e) remove nonexistent
    {
        SortedList sl;
        sl.insert("apple");
        sl.remove("cherry");
        assert(sl.size() == 1);
        cout << "  (e) remove nonexistent" << endl;
    }

    // (f) clear
    {
        SortedList sl;
        sl.insert("apple");
        sl.insert("banana");
        sl.clear();
        assert(sl.size() == 0);
        cout << "  (f) clear" << endl;
    }

    // (g) is_sorted_by_length
    {
        SortedList sl(SortedList::SortOrder::LENGTH);
        assert(sl.is_sorted_by_length());
        assert(!sl.is_sorted_lexicographically());
        cout << "  (g) is_sorted_by_length" << endl;
    }

    // (h) is_sorted_lexicographically
    {
        SortedList sl;
        assert(sl.is_sorted_lexicographically());
        assert(!sl.is_sorted_by_length());
        cout << "  (h) is_sorted_lexicographically" << endl;
    }

    // (i) size
    {
        SortedList sl;
        assert(sl.size() == 0);
        sl.insert("apple");
        assert(sl.size() == 1);
        sl.insert("banana");
        assert(sl.size() == 2);
        cout << "  (i) size" << endl;
    }

    // (j) get_strings
    {
        SortedList sl;
        sl.insert("banana");
        sl.insert("apple");
        vector<string> v = sl.get_strings();
        assert(v.size() == 2);
        assert(v[0] == "apple");
        assert(v[1] == "banana");
        cout << "  (j) get_strings" << endl;
    }

    // (k) get_string
    {
        SortedList sl;
        sl.insert("banana");
        sl.insert("apple");
        assert(sl.get_string(0) == "apple");
        assert(sl.get_string(1) == "banana");
        cout << "  (k) get_string" << endl;
    }

    // (k) get_string out of range
    {
        SortedList sl;
        sl.insert("apple");
        try {
            sl.get_string(5);
            assert(false);
        } catch (const out_of_range &) {}
        cout << "  (k) get_string out of range throws" << endl;
    }

    // (l) sort_by_length
    {
        SortedList sl;
        sl.insert("banana");
        sl.insert("hi");
        sl.insert("apple");
        sl.sort_by_length();
        assert(sl.is_sorted_by_length());
        assert(sl.get_string(0) == "hi");
        assert(sl.get_string(1) == "apple");
        assert(sl.get_string(2) == "banana");
        cout << "  (l) sort_by_length" << endl;
    }

    // (m) sort_lexicographically
    {
        SortedList sl(SortedList::SortOrder::LENGTH);
        sl.insert("banana");
        sl.insert("hi");
        sl.insert("apple");
        sl.sort_lexicographically();
        assert(sl.is_sorted_lexicographically());
        assert(sl.get_string(0) == "apple");
        assert(sl.get_string(1) == "banana");
        assert(sl.get_string(2) == "hi");
        cout << "  (m) sort_lexicographically" << endl;
    }
}

// ── Car / GasStation ──────────────────────────────────────────────────────────

void test_cars() {
    cout << "Location" << endl;

    {
        Location a = {0, 0};
        Location b = {3, 4};
        assert(near(a.distance_to(b), 5.0f));
        cout << "  distance_to" << endl;
    }

    cout << "Car" << endl;

    {
        Car c;
        assert(near(c.get_location().x, 0));
        assert(near(c.get_location().y, 0));
        assert(near(c.get_mpg(), 0));
        assert(near(c.get_fuel_capacity(), 0));
        assert(near(c.get_fuel_level(), 0));
        cout << "  default constructor" << endl;
    }

    {
        Car c({1, 2}, 30.0f, 15.0f);
        assert(near(c.get_location().x, 1));
        assert(near(c.get_location().y, 2));
        assert(near(c.get_mpg(), 30.0f));
        assert(near(c.get_fuel_capacity(), 15.0f));
        assert(near(c.get_fuel_level(), 15.0f));  // starts full
        cout << "  parameterized constructor" << endl;
    }

    {
        Car a({0, 0}, 30.0f, 10.0f);
        Car b(a);
        assert(near(b.get_mpg(), 30.0f));
        assert(near(b.get_fuel_level(), 10.0f));
        cout << "  copy constructor" << endl;
    }

    {
        Car c({0, 0}, 30.0f, 10.0f);  // 30 mpg, 10 gal -> 300 mile range
        bool moved = c.move_to({3, 4});  // distance = 5 miles
        assert(moved);
        assert(near(c.get_location().x, 3));
        assert(near(c.get_location().y, 4));
        assert(near(c.get_fuel_level(), 10.0f - 5.0f / 30.0f));
        cout << "  move_to success" << endl;
    }

    {
        Car c({0, 0}, 30.0f, 0.1f);  // barely any fuel
        bool moved = c.move_to({100, 0});
        assert(!moved);
        assert(near(c.get_location().x, 0));  // didn't move
        cout << "  move_to fails (not enough fuel)" << endl;
    }

    cout << "GasStation" << endl;

    {
        GasStation gs({5, 5}, 3.50f);
        assert(near(gs.get_location().x, 5));
        assert(near(gs.get_location().y, 5));
        assert(near(gs.get_dollars_per_gallon(), 3.50f));
        cout << "  parameterized constructor" << endl;
    }

    cout << "move_cars" << endl;

    {
        vector<Car> cars = {Car({0,0}, 30.0f, 10.0f), Car({0,0}, 30.0f, 10.0f)};
        Location dest = {3, 4};
        vector<Car> result = move_cars(cars, dest);
        assert(result.size() == 2);
        cout << "  (b) all cars reach destination" << endl;
    }

    {
        vector<Car> cars = {Car({0,0}, 30.0f, 10.0f), Car({0,0}, 30.0f, 0.0f)};
        Location dest = {3, 4};
        vector<Car> result = move_cars(cars, dest);
        assert(result.size() == 1);
        cout << "  (b) car with no fuel excluded" << endl;
    }

    {
        Car c({0, 0}, 10.0f, 5.0f);   // 10 mpg, 5 gal -> 50 mile range
        GasStation gs({40, 0}, 4.0f);  // station at mile 40
        Location dest = {90, 0};        // destination at mile 90
        vector<Car> cars = {c};
        vector<GasStation> stations = {gs};
        pair<vector<Car>, vector<float>> result = move_cars(cars, dest, stations);
        assert(result.first.size() == 1);
        assert(result.second.size() == 1);
        cout << "  (c) car reaches via gas station" << endl;
    }
}

int main() {
    test_sorted_list();
    cout << endl;
    test_cars();
    cout << endl << "all tests passed" << endl;
    return 0;
}
