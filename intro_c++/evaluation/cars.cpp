#include <iostream>
#include "cars.hpp"

using namespace std;

float Location::distance_to(const Location &other) const {
    float dx = x - other.x;
    float dy = y - other.y;
    return std::sqrt(dx*dx + dy*dy);
}

Car::Car() 
    : location({0, 0}),
      mpg(0), 
      fuel_capacity(0), 
      fuel_level(0) 
{}

Car::Car(const Location &location, float mpg, float fuel_capacity) 
    : location(location),
      mpg(mpg), 
      fuel_capacity(fuel_capacity), 
      fuel_level(fuel_capacity) 
{}

Car::Car(const Car &other) 
    : location(other.location),
      mpg(other.mpg), 
      fuel_capacity(other.fuel_capacity), 
      fuel_level(other.fuel_level) 
{}

Car::~Car() {}

Location Car::get_location() const {
    return location;
}

float Car::get_mpg() const {
    return mpg;
}

float Car::get_fuel_capacity() const {
    return fuel_capacity;
}

float Car::get_fuel_level() const {
    return fuel_level;
}

void Car::set_location(const Location &location) {
    this->location = location;
}

void Car::set_mpg(float mpg) {
    this->mpg = mpg;
}

void Car::set_fuel_capacity(float fuel_capacity) {
    this->fuel_capacity = fuel_capacity;
}

void Car::set_fuel_level(float fuel_level) {
    this->fuel_level = fuel_level;
}

bool Car::move_to(const Location &destination) {
    float distance = location.distance_to(destination);
    float fuel_needed = distance / mpg;
    if (fuel_needed <= fuel_level) {
        fuel_level -= fuel_needed;
        location = destination;
        return true;
    }
    return false;
}

GasStation::GasStation() 
    : location({0, 0}),
      dollars_per_gallon(0) 
{}

GasStation::GasStation(const Location &location, float dollars_per_gallon) 
    : location(location),
      dollars_per_gallon(dollars_per_gallon) 
{}

GasStation::GasStation(const GasStation &other) 
    : location(other.location),
      dollars_per_gallon(other.dollars_per_gallon) 
{}

GasStation::~GasStation() {}

Location GasStation::get_location() const {
    return location;
}

float GasStation::get_dollars_per_gallon() const {
    return dollars_per_gallon;
}

void GasStation::set_location(const Location &location) {
    this->location = location;
}

void GasStation::set_dollars_per_gallon(float dollars_per_gallon) {
    this->dollars_per_gallon = dollars_per_gallon;
}

vector<Car> move_cars (const vector<Car> &cars, const Location &destination) {
    vector<Car> moved_cars;
    for (Car car : cars) {
        // car is a copy of the original car here
        if (car.move_to(destination)) {
            moved_cars.push_back(car);
        }
    }
    return moved_cars;
}

pair<vector<Car>, vector<float>> move_cars (const vector<Car> &cars, const Location &destination, const vector<GasStation> &gas_stations){
    vector<Car> moved_cars = vector<Car>();
    vector<float> fuel_costs = vector<float>();

    for (Car car : cars) {
        // car is a copy of the original car here
        if (!car.move_to(destination)) {
            // Try to find a gas station we can reach
            float fuel_cost = 0; 
            for (const GasStation &station : gas_stations) {
                float distance_to_station = car.get_location().distance_to(station.get_location());
                float fuel_needed_to_station = distance_to_station / car.get_mpg();
                // we will only move to one station at most
                // gas stations earlier in the list will be prioritized over later ones
                if (fuel_needed_to_station <= car.get_fuel_level()) {
                    car.move_to(station.get_location());
                    // fully refuel at the station before moving to the destination
                    fuel_cost = (car.get_fuel_capacity() - car.get_fuel_level()) * station.get_dollars_per_gallon();
                    car.set_fuel_level(car.get_fuel_capacity());
                    break;
                }
            }
            if (car.move_to(destination)) {
                moved_cars.push_back(car);
                fuel_costs.push_back(fuel_cost);
            }
        } else {
            moved_cars.push_back(car);
            fuel_costs.push_back(0);
        }
    }
    return {moved_cars, fuel_costs};
}
