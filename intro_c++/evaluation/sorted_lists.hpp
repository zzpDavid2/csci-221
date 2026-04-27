#ifndef SORTED_LISTS_HPP
#define SORTED_LISTS_HPP

#include <vector>
class SortedList {
public:
    enum class SortOrder {
        LENGTH,
        LEXICOGRAPHIC
    };
    
    // constructors
    SortedList(); // (a)
    SortedList(const SortedList &other); // (b)
    SortedList(SortOrder order); // (c)
    ~SortedList();

    // getters
    SortOrder get_sort_order() const;
    bool is_sorted_by_length() const; // (g)
    bool is_sorted_lexicographically() const; // (h)
    size_t size() const; // (i)
    std::vector<std::string> get_strings() const; // (j)
    std::string get_string(size_t index) const; // (k)

    // setters
    void sort_by_length(); // (l)
    void sort_lexicographically(); // (m)

    // operations
    void insert(const std::string &str); // (d)
    void remove(const std::string &str); // (e)
    void clear(); // (f)

private:
    struct Node {
        std::string data;
        Node *next;

        Node(const std::string &data) : data(data), next(nullptr) {}
    };
    SortOrder sort_order;
    Node *head;
    size_t length;

protected:
};


#endif // SORTED_LISTS_HPP
