#include "sorted_lists.hpp"
#include <string>

// (a) default constructor
SortedList::SortedList() 
    : sort_order(SortOrder::LEXICOGRAPHIC),
      head(nullptr),
      length(0)
{}

// (b) copy constructor
SortedList::SortedList(const SortedList &other) {
    sort_order = other.sort_order;
    head = nullptr;
    length = 0;
    if (other.head == nullptr) {
        head = nullptr;
        return;
    }
    std::vector<std::string> strings = other.get_strings();
    for (const std::string &str : strings) {
        insert(str);
    }
}

// (c) constructor with sort order
SortedList::SortedList(SortOrder order) {
    sort_order = order;
    head = nullptr;
    length = 0;
}

SortedList::~SortedList() {
    clear();
}

// getters

SortedList::SortOrder SortedList::get_sort_order() const {
    return sort_order;
}

// (g)
bool SortedList::is_sorted_by_length() const {
    return sort_order == SortOrder::LENGTH;
}

// (h)
bool SortedList::is_sorted_lexicographically() const {
    return sort_order == SortOrder::LEXICOGRAPHIC;
}

// (i)
size_t SortedList::size() const {
    return length;
}

// (j)
std::vector<std::string> SortedList::get_strings() const {
    // C++ RVO optimizes this to avoid copying the vector
    std::vector<std::string> strings;
    const Node *current = head;
    while (current != nullptr) {
        strings.push_back(current->data);
        current = current->next;
    }
    return strings;
}

// (k)
std::string SortedList::get_string(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of bounds");
    }
    const Node *current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

// setters

// (l)
void SortedList::sort_by_length() {
    std::vector<std::string> strings = get_strings();
    clear();
    sort_order = SortOrder::LENGTH;
    for (const std::string &str : strings) {
        insert(str);
    }
}

// (m)
void SortedList::sort_lexicographically() {
    std::vector<std::string> strings = get_strings();
    clear();
    sort_order = SortOrder::LEXICOGRAPHIC;
    for (const std::string &str : strings) {
        insert(str);
    }
}

// operations

// (d)
void SortedList::insert(const std::string &str) {
    Node *prev = nullptr;
    Node *current = head;
    Node *new_node = new Node(str);
    while (current != nullptr) {
        // Check if the new string should be inserted before the current node
        if ((sort_order == SortOrder::LENGTH && str.length() < current->data.length()) ||
            (sort_order == SortOrder::LEXICOGRAPHIC && str < current->data)) {
            new_node->next = current;
            if (prev == nullptr) {
                head = new_node;
            } else {
                prev->next = new_node;
            }
            length++;
            return;
        }
        // Insert the new node at the end if we reach the end of the list
        if (current->next == nullptr) {
            current->next = new_node;
            length++;
            return;
        }
        prev = current;
        current = current->next;
    }
    head = new_node;
    length++;
}

// (e)
void SortedList::remove(const std::string &str) {
    Node *prev = nullptr;
    Node *current = head;
    while (current != nullptr) {
        if (current->data == str) {
            Node *next = current->next;
            // Remove the current node
            if (prev != nullptr) {
                prev->next = next;
            } else {
                head = next;
            }
            delete current;
            length--;
            // Move to the next node after deletion
            current = next;
            continue;
        }
        prev = current;
        current = current->next;
    }
}

// (f)
void SortedList::clear() {
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    length = 0;
}
