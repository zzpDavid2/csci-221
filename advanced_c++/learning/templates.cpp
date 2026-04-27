#include "templates.hpp"
#include <iostream>
#include <string>

int main() {
    // (a): duplicate
    std::string s = "hello";
    std::string *s_copy = duplicate(s);
    std::cout << "original: " << s << std::endl;
    std::cout << "duplicate: " << *s_copy << std::endl;
    delete s_copy;

    int x = 42;
    int *x_copy = duplicate(x);
    std::cout << "original: " << x << std::endl;
    std::cout << "duplicate: " << *x_copy << std::endl;
    delete x_copy;

    // (b): CountedCopies
    CountedCopies<std::string> cc("hello");
    cc.add_copy_count(3);
    std::cout << "copy count: " << cc.get_copy_count() << std::endl;
    cc.remove_copy_count(1);
    std::cout << "copy count after remove: " << cc.get_copy_count() << std::endl;

    // checkout a copy
    std::string *checked_out = cc.copy();
    std::cout << "checked out: " << *checked_out << std::endl;
    std::cout << "copy count after checkout: " << cc.get_copy_count() << std::endl;
    delete checked_out;

    return 0;
}
