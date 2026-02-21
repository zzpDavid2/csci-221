# Pointers and Arrays

## Implementation

### Linked list
I implemented a singly linked list with a `linked_list_t` header that stores the list size and a pointer to the first node. Nodes are `node_t` structs with a `data_value` and `next_node` pointer. The list helpers include:

- `new_list(size, initial_value)` to allocate a list and populate it with `size` nodes.
- `get_node(list, index)` to walk the list to a zero-based index.
- `append_to_list(list, value)` to add a node at the end.
- `delete_node(node_pp)` to remove a node via a pointer-to-pointer. `node_pp` is a pointer to the pointer of the node that we are going to remove. The code will get the `next_node` of the current node and replace the current node with it.
- `delete_value_from_list(list, value)` to remove all nodes with a matching value and decrement `list->size`.
- `delete_list(list)` to free all nodes and the list header.

The key design choice was using pointer-to-pointer traversal in `delete_value_from_list` so deletions can update the list head without special casing the first node.

### Arrays and strings
I implemented `remove_odds(array, size)` to create a new heap-allocated array containing only even values from the input. I used a second index (`new_size`) to compact the results. I also implemented `find_char(string, target)` to return a pointer to the first matching character and `get_string_length(string)` using pointer arithmetic.

## Testing
I used the `main` function in [pointers_and_arrays/evaluation/pointers.c](pointers.c) to test:

- **Linked list creation and access**: Created a list of 10 nodes with value 2, then printed the last node value repeatedly to confirm `new_list` and `get_node` work.
- **Append**: Appended a value (4) and printed the new last node to verify `append_to_list` updates size and links.
- **Delete by value**: Called `delete_value_from_list(list, 2)` and printed the list size afterward to confirm deletions and size tracking.
- **Delete list**: Created and freed a second list to validate `delete_list` does not leak or crash. I didn't find a more satisfying way to test this code. 
- **remove_odds**: Built a small array, called `remove_odds`, and printed the result to check the compacted even values.
- **find_char**: Searched for `'o'` in "Hello, World!" and printed the found character.
- **get_string_length**: Printed the length of "Hello, World!" to confirm pointer-based counting.
- **argv printing**: Read a separator from stdin and printed `argv` joined by that separator.

These tests are simple sanity checks that each function works on a typical input. They do not exhaust edge cases.

## Bugs / Limitations

- `remove_odds` returns an array of length `size` but does not return the new length. The caller still prints 10 elements, so the trailing entries after the last even value are default-initialized to 0. 

Overall, the functions work on the tested cases.