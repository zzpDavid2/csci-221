#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_t {
    char *data_str;
    struct node_t *left;
    struct node_t *right;
} node_t;

typedef struct binary_search_tree_t {
    size_t size;
    node_t *root;
} binary_search_tree_t;

typedef enum order_t {
    GREATER = 1,
    EQUAL = 0,
    LESS = -1
} order_t;

// String comparison utility functions

// compare_str: Returns comparison result (GREATER, EQUAL, LESS)
order_t compare_str(char *a_str, char *b_str);

// get_str_len: Returns length of null-terminated string
size_t get_str_len(char *str);

// copy_str: Returns copy of input string
char *copy_str(char *str);

// Node and tree creation

// new_node: Creates and returns new BST node with copied string data
node_t *new_node(char *data_str);

// new_bst: Creates and returns new tree with single root node
binary_search_tree_t *new_bst(char *root_str);

// Tree operations

// find_node_location: Recursively finds where string should be in tree; returns pointer-to-pointer for parent link updates
node_t **find_node_location(node_t **node_pp, char *data_str, size_t *depth);

// insert_to_subtree: Internal function to insert into subtree; used by insert()
void insert_to_subtree(node_t *node, char *data_str, size_t depth);

// insert: Public interface to add string to tree
void insert(binary_search_tree_t *tree, char *data_str);

// Node and tree removal

// free_node: Frees single node only (preserves children)
void free_node(node_t *node);

// remove_from_subtree: Removes node; handles leaf, one child, and two child cases
void remove_from_subtree(node_t **node_pp);

// remove_str_from_tree: Public interface to remove string from tree; returns 1 if found, 0 otherwise
u_int8_t remove_str_from_tree(binary_search_tree_t *tree, char *data_str);

// delete_tree: Recursively frees entire tree and all nodes
void delete_tree(binary_search_tree_t *tree);

#endif // BINARY_SEARCH_TREE_H
