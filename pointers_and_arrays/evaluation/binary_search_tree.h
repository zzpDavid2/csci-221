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

// Node and tree creation

// new_node: Creates and returns new BST node with copied string data
node_t *new_node(char *data_str);

// new_bst: Creates and returns new tree with single root node
binary_search_tree_t *new_bst(char *root_str);

// String helper

// compare_str: Returns comparison result (GREATER, EQUAL, LESS)
// I put this here in the public header because part (c) specifically asks for it
order_t compare_str(char *a_str, char *b_str);

// Tree operations

// insert: Public interface to add string to tree
void insert(binary_search_tree_t *tree, char *data_str);

// Node and tree removal

// remove_str_from_tree: Public interface to remove string from tree; returns 1 if found, 0 otherwise
u_int8_t remove_str_from_tree(binary_search_tree_t *tree, char *data_str);

// delete_tree: Frees entire tree and all nodes
void delete_tree(binary_search_tree_t *tree);

#endif // BINARY_SEARCH_TREE_H
