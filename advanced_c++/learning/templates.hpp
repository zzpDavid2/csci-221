#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <cstdint>

template<typename T>
T *duplicate(const T &value) {
    return new T(value);
}

template<typename T>
class CountedCopies {
private:
    T object;
    uint32_t copy_count;
public:
    CountedCopies() {}
    CountedCopies(const T &object) : object(object), copy_count(0) {}
    CountedCopies(const CountedCopies &other) {
        object = other.object;
        copy_count = other.copy_count;
    }
    ~CountedCopies() {}

    void add_copy_count(uint32_t count) {
        copy_count+=count;
    }

    void remove_copy_count(uint32_t count) {
        copy_count-=count;
    }

    uint32_t get_copy_count() const {
        return copy_count;
    }

    T *copy() {
        if (copy_count == 0) {
            return nullptr;
        }
        copy_count--;
        return duplicate<T>(object);
    }
};

#endif // TEMPLATES_HPP