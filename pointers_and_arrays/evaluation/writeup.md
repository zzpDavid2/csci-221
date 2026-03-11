# Pointers and Arrays - Evaluation

## Implementation

### Binary Search Tree

I implemented a binary search tree with string keys. The tree uses two main structs:
- `node_t`: Contains a `char *data_str` for the key, and pointers to `left` and `right` children
- `binary_search_tree_t`: Header that stores the tree `size` and a pointer to the `root` node

The BST implementation includes these helper functions:

**String utilities:**
- `compare_str(a_str, b_str)`: Returns `GREATER`, `EQUAL`, or `LESS` based on lexicographic comparison. Handles NULL strings gracefully.
- `get_str_len(str)`: Returns string length using pointer arithmetic with overflow protection.
- `copy_str(str)`: Creates a heap-allocated copy of a string, needed because string literals are immutable.

**Tree operations:**
- `new_bst(root_str)`: Creates a new BST with a single root node.
- `new_node(data_str)`: Allocates a new node and copies the string data.
- `find_node_location(node_pp, data_str, depth)`: Recursively finds where a string should be located in the tree. Returns a pointer-to-pointer so the caller can modify parent links. Uses depth tracking to prevent infinite recursion.
- `insert_to_subtree(node, data_str, depth)` and `insert(tree, data_str)`: Add a new string to the tree, maintaining BST property.
- `remove_from_subtree(node_pp)`: Removes a node handling three cases: leaf nodes, nodes with one child, and nodes with two children. For two-child nodes, it finds the in-order predecessor (rightmost node in left subtree) to replace the deleted node's value.
- `remove_str_from_tree(tree, data_str)`: Finds and removes a string from the tree, returning 1 if successful, 0 if not found.
- `free_subtree(node)`: Recursively frees all nodes in a subtree.
- `free_node(node)`: Frees a single node and its string (used during removal to avoid freeing children).
- `delete_tree(tree)`: Frees entire tree including all nodes and the tree structure.

**Key design choices:**
- Used pointer-to-pointer (`node_t **`) in `find_node_location` and `remove_from_subtree` to enable modifying parent pointers without special-casing the root node.
- Separated `free_subtree` (recursive) from `free_node` (single node) to properly handle memory during removal operations where children need to be preserved.
- All error messages wrapped in `#if DEBUG == 1` blocks for clean production builds.

## Testing

I created a comprehensive test suite in [tests.c](tests.c) with separate test functions for each component. All tests use assertions to verify correctness.

Additionally, I used a debugger to track the state of the tree over the run. 

### I/O String Manipulation

I implemented a command-line utility in [io.c](io.c) that reads a string and repeat count from user input, then prints the string the specified number of times. An optional command-line flag `-r` reverses the string output.

**Main functionality:**
- `reverse_print(str)`: Recursively prints a string in reverse order. Advances through the string with `str + 1` in the recursive call, then prints the current character when backtracking up the call stack. The null terminator serves as the base case.
- `main(argc, argv)`: Prompts user for a string and an integer repeat count. Safely checks for the `-r` command-line argument by verifying `argc > 1` before accessing `argv[1]`. For each iteration, prints the string either normally or reversed.

**Key implementation details:**
- Recursion strategy: `reverse_print` leverages call stack depth to achieve reversal - it recurses to the string's end, then backtracks while printing characters.

## Testing
I tested the command line interface and it works as expected both with and without `-r`.

## Bugs / Limitations

- All test cases works.
- Both programs should work to my knowledge.
