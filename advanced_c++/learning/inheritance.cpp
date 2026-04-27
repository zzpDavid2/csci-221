#include "inheritance.hpp"
#include <memory>

using namespace std;

// Location

Location::Location()
    : x(0), y(0), name(std::make_unique<std::string>(""))
{}

Location::Location(double x, double y, const std::string &name)
    : x(x), y(y), name(std::make_unique<std::string>(name))
{}

Location::Location(const Location &other)
    : x(other.x), y(other.y), name(std::make_unique<std::string>(*other.name))
{}

Location::~Location() {}

double Location::get_x() const { return x; }
double Location::get_y() const { return y; }

std::string Location::get_name() const { return *name; }

void Location::set_x(double x) { this->x = x; }
void Location::set_y(double y) { this->y = y; }
void Location::set_name(const std::string &name) { *this->name = name; }

void Location::print(std::ostream &os) const {
    os << "Location(" << x << ", " << y << ", " << *name << ")";
}

std::ostream& operator<<(std::ostream &os, const Location &location) {
    location.print(os);
    return os;
}

// Building
Building::Building()
    : Location(), area(0), num_floors(0)
{}

Building::Building(double x, double y, const std::string &name, double area, uint32_t num_floors)
    : Location(x, y, name), area(area), num_floors(num_floors)
{}

Building::Building(const Building &other)
    : Location(other), area(other.area), num_floors(other.num_floors)
{}

Building::~Building() {}

double Building::get_area() const { return area; }
uint32_t Building::get_num_floors() const { return num_floors; }

void Building::set_area(double area) { this->area = area; }
void Building::set_num_floors(uint32_t num_floors) { this->num_floors = num_floors; }

void Building::print(std::ostream &os) const {
    os << "Building(" << get_x() << ", " << get_y() << ", " << get_name() << ", " << get_area() << ", " << get_num_floors() << ")";
}

// OfficeBuilding
OfficeBuilding::OfficeBuilding()
    : Building(), num_cubicles(0), num_offices(0)
{}

std::ostream& operator<<(std::ostream &os, const Building &building){
    building.print(os);
    return os;
}

OfficeBuilding::OfficeBuilding(
    double x, 
    double y, 
    const std::string &name, 
    double area, 
    uint32_t num_floors, 
    uint32_t num_cubicles, 
    uint32_t num_offices)
    : Building(x, y, name, area, num_floors),
      num_cubicles(num_cubicles),
      num_offices(num_offices)
{}

int main()
{
    Building b(1, 2, "My Building", 1000, 5);
    // cout << b.get_x() << endl;
    b.print(cout);
    cout << endl;

    Location *loc = &b;

    loc->print(cout);
    cout << endl;

    return 0;
}

