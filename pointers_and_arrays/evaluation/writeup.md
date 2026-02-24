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

I created a comprehensive test suite in [tests.c](tests.c) with separate test functions for each component:

- `test_compare_str()`: Tests string comparison including equal strings, greater/less than cases, and NULL handling.
- `test_get_str_len()`: Verifies string length calculation for empty strings and normal cases.
- `test_copy_str()`: Confirms strings are copied to new memory addresses with identical content, and NULL handling.
- `test_new_bst()`: Validates tree creation, initial size, and root node properties.
- `test_insert()`: Creates a tree with multiple values ("dog", "cat", "ant", "elephant", "zebra") and verifies the BST structure by checking left/right child relationships.
- `test_find_node_location()`: Tests finding existing nodes in the tree.
- `test_remove_str_from_tree()`: Tests three scenarios:
  - Removing a leaf node and verifying parent pointer is NULL
  - Removing a node with one child and verifying the child replaces it
  - Attempting to remove a non-existent node returns 0
- `test_delete_tree()`: Creates a tree with multiple nodes and frees it to check for memory leaks (manual verification).
- `test_comprehensive()`: Builds a larger tree with 10+ fruit names, performs multiple removals, and verifies no crashes.

All tests use assertions to verify correctness. The tests caught the critical insertion bug during development.

## Bugs / Limitations

- No rebalancing implemented, so the tree can become unbalanced with certain insertion orders (e.g., inserting sorted strings creates a linked list).
