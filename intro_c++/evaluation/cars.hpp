#ifndef CARS_HPP
#define CARS_HPP

#include <vector>
#include <utility>

struct Location {
    float x;
    float y;
    float distance_to(const Location &other) const;
};

class Car {
public:
    // constructors
    Car();
    Car(const Car &other);
    Car(const Location &location, float mpg, float fuel_capacity);
    ~Car();

    // returns true and moves if move successful, 
    // returns false and doesn't move if not enough fuel
    bool move_to(const Location &destination);

    // getters
    Location get_location() const;
    float get_mpg() const;
    float get_fuel_capacity() const;
    float get_fuel_level() const;

    // setters
    void set_location(const Location &location);
    void set_mpg(float mpg);
    void set_fuel_capacity(float fuel_capacity);
    void set_fuel_level(float fuel_level);

private:
    Location location;
    float mpg;
    float fuel_capacity;
    float fuel_level;
protected:
};

class GasStation {
public:
    // constructors
    GasStation();
    GasStation(const GasStation &other);
    GasStation(const Location &location, float dollars_per_gallon);
    ~GasStation();

    // getters
    Location get_location() const;
    float get_dollars_per_gallon() const;

    // setters
    void set_location(const Location &location);
    void set_dollars_per_gallon(float dollars_per_gallon);

private:
    Location location;
    float dollars_per_gallon;
protected:
};

// (b)
std::vector<Car> move_cars (const std::vector<Car> &cars, const Location &destination);
// (c)
std::pair<std::vector<Car>, std::vector<float>> move_cars (const std::vector<Car> &cars, const Location &destination, const std::vector<GasStation> &gas_stations);

#endif // CARS_HPP

