#ifndef INHERITANCE_HPP
#define INHERITANCE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <cstdint>

class Location {
protected:
    double x;
    double y;
private:
    // double x;
    // double y;
    std::unique_ptr<std::string> name;
public:
    // constructors
    Location();
    Location(double x, double y, const std::string &name);
    Location(const Location &other);
    ~Location();

    // getters
    double get_x() const;
    double get_y() const;
    std::string get_name() const;

    // setters
    void set_x(double x);
    void set_y(double y);
    void set_name(const std::string &name);

    virtual void print(std::ostream &os) const;

    friend std::ostream& operator<<(std::ostream &os, const Location &location);
};

class Building : public Location {
private:
    double area;
    uint32_t num_floors;
public:
    // constructors
    Building();
    Building(double x, double y, const std::string &name, double area, uint32_t num_floors);
    Building(const Building &other);
    ~Building();

    // getters
    double get_area() const;
    uint32_t get_num_floors() const;

    // setters
    void set_area(double area);
    void set_num_floors(uint32_t num_floors);

    virtual void print(std::ostream &os) const;

    friend std::ostream& operator<<(std::ostream &os, const Building &building);
protected:
};

class OfficeBuilding : public Building {
private:
    uint32_t num_cubicles;
    uint32_t num_offices;
public:
    // constructors
    OfficeBuilding();
    OfficeBuilding(
        double x, 
        double y, 
        const std::string &name, 
        double area, 
        uint32_t num_floors, 
        uint32_t num_cubicles, 
        uint32_t num_offices);
    OfficeBuilding(const OfficeBuilding &other);
    ~OfficeBuilding();

    // getters
    uint32_t get_num_cubicles() const;
    uint32_t get_num_offices() const;

    // setters
    void set_num_cubicles(uint32_t num_cubicles);
    void set_num_offices(uint32_t num_offices);
};

#endif // INHERITANCE_HPP