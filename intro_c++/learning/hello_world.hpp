#ifndef HELLO_WORLD_HPP
#define HELLO_WORLD_HPP

#include <iostream>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

class CharacterCount {
public:
    // constructors
    CharacterCount();
    CharacterCount(std::string str);
    CharacterCount(const CharacterCount &other);

    // destructor
    ~CharacterCount();

    // getters
    std::string get_string() const;
    const std::vector<uint32_t>& get_array() const;

    // setters
    void set_string(std::string str);
    void set_array(const std::vector<uint32_t>& arr);

    // operators
    uint32_t *operator[](size_t index);
private:
    std::string s;
    std::vector<uint32_t> counts;
protected:
};

#endif // HELLO_WORLD_HPP