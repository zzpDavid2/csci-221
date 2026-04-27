#ifndef STL_HPP
#define STL_HPP

#include <iostream>
#include <cstdint> 

class Tracer {
private:
    static uint32_t head;
    uint32_t id;
public:
    Tracer();
    Tracer(const Tracer &other);
    ~Tracer();

    uint32_t get_id() const;
    void operator=(const Tracer &other);
    bool operator<(const Tracer &other) const;
protected:
};

#endif // STL_HPP