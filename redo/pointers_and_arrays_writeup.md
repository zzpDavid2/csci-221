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

### Binary Search Tree Tests

Tests are in [tests.c](tests.c). Each test function uses `assert` to verify correctness.

#### String Helper Tests

| Test Call | Expected | Actual | Pass | What this test checks |
|---|---|---|---|---|
| `compare_str("hello", "hello")` | `EQUAL` | `EQUAL` | Yes | Equal strings |
| `compare_str("", "")` | `EQUAL` | `EQUAL` | Yes | Empty strings |
| `compare_str("world", "hello")` | `GREATER` | `GREATER` | Yes | Lexicographically greater |
| `compare_str("hello", "world")` | `LESS` | `LESS` | Yes | Lexicographically less |
| `compare_str(NULL, "hello")` | `LESS` | `LESS` (prints debug: `compare_str failed. a_str is NULL`) | Yes | NULL left argument handled gracefully |
| `compare_str("hello", NULL)` | `GREATER` | `GREATER` (prints debug: `compare_str failed. b_str is NULL`) | Yes | NULL right argument handled gracefully |
| `get_str_len("")` | `0` | `0` | Yes | Empty string length |
| `get_str_len("hello")` | `5` | `5` | Yes | Normal string length |
| `get_str_len("Hello, World!")` | `13` | `13` | Yes | String with punctuation |
| `copy_str("test string")` returns different address | `true` | `true` | Yes | Copy is a new allocation |
| `copy_str("test string")` content matches | `true` | `true` | Yes | Copy content is correct |
| `copy_str(NULL)` | `NULL` | `NULL` (prints debug: `copy_str: str is NULL`) | Yes | NULL input handled |

#### BST Structure Tests

| Test Call | Expected | Actual | Pass | What this test checks |
|---|---|---|---|---|
| `new_bst("root")->size` | `1` | `1` | Yes | Initial tree size |
| `new_bst("root")->root->data_str` | `"root"` | `"root"` | Yes | Root data stored correctly |
| `new_bst("root")->root->left` | `NULL` | `NULL` | Yes | Root starts with no left child |
| `new_bst("root")->root->right` | `NULL` | `NULL` | Yes | Root starts with no right child |
| Insert `"cat"`, `"ant"` left of `"dog"` | `"cat"` at left, `"ant"` at left-left | matches | Yes | Left subtree insertion order |
| Insert `"elephant"`, `"zebra"` right of `"dog"` | `"elephant"` at right, `"zebra"` at right-right | matches | Yes | Right subtree insertion order |

#### Removal Tests

| Test | Expected | Actual | Pass | What this test checks |
|---|---|---|---|---|
| Remove leaf `"a"` from tree (root `"m"`, left `"a"`, right `"z"`) | `root->left == NULL` | `NULL` | Yes | Leaf node removal |
| Remove `"a"` (parent of `"b"`) from tree | `root->left == "b"` | `"b"` | Yes | One-child removal replaces with child |
| Remove `"nonexistent"` | returns `0` | `0` | Yes | Not-found returns 0 |
| Remove `"banana"`, `"grape"`, `"peach"` from 11-node tree, then `delete_tree` | no crash | no crash | Yes | Multi-removal stability |
| `delete_tree` on 5-node tree | no crash, no leaks | no crash | Yes | Full tree deallocation |
| `remove_str_from_tree(NULL, "test")` | returns `0`, no crash | `0` (prints debug: `remove_str_from_tree: tree is NULL`) | Yes | NULL tree guard (redo fix) |
| `delete_tree(NULL)` | no crash | no crash (prints debug: `delete_tree: tree is NULL`) | Yes | NULL tree guard (redo fix) |

#### How Tests Were Run

From `redo/`:
1. `make tests`
2. `./tests`

Output summary: `=== All tests passed! ===` with no assertion failures or segfaults.

### I/O String Manipulation Tests

#### How Tests Were Run

Built with `make io`, then ran with input piped via `printf "string\ncount\n" | ./io [flags]`.
The Makefile's `run` target covers the four flag combinations shown below.

| Command | Input (string, count) | Expected Output | Actual Output | Pass | What this test checks |
|---|---|---|---|---|---|
| `./io` | `hello`, `3` | `hello` × 3 | `hello` `hello` `hello` | Yes | Normal print, no flag |
| `./io -r` | `hello`, `2` | `olleh` × 2 | `olleh` `olleh` | Yes | `-r` as `argv[1]` |
| `./io -abr` | `hello`, `2` | `olleh` × 2 | `olleh` `olleh` | Yes | `-r` inside compound flag `-abr` (redo fix: check each char) |
| `./io -a -r` | `hello`, `2` | `olleh` × 2 | `olleh` `olleh` | Yes | `-r` as `argv[2]` (redo fix: loop over all args) |
| `./io -r` | `abc`, `1` | `cba` | `cba` | Yes | Reversal correctness |
| `./io` | `hello`, `0` | (no output) | (no output) | Yes | Zero repeat count |
| `./io` | `x`, `1` | `x` | `x` | Yes | Single character string |
| `./io` | `notanint`, then `2` | re-prompts, then `hello` × 2 | `Invalid integer input. Try again.` then `hello` `hello` | Yes | Invalid integer triggers re-prompt |
| `./io` | `-5`, then `1` | re-prompts, then `hello` × 1 | `Only positive integers allowed. Try again.` then `hello` | Yes | Negative integer rejected |

## Bugs / Limitations

- All test cases pass.
- The `-r` flag is now recognized in any argument position (not only `argv[1]`).
- `delete_tree(NULL)` and `remove_str_from_tree(NULL, ...)` are now guarded against NULL input and return safely.
