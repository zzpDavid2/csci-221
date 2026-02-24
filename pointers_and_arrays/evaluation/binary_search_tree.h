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
order_t compare_str(char *a_str, char *b_str);
size_t get_str_len(char *str);
char *copy_str(char *str);

// Node and tree creation
node_t *new_node(char *data_str);
binary_search_tree_t *new_bst(char *root_str);

// Tree operations
node_t **find_node_location(node_t **node_pp, char *data_str, size_t *depth);
void insert_to_subtree(node_t *node, char *data_str, size_t depth);
void insert(binary_search_tree_t *tree, char *data_str);

// Node and tree removal
void free_node(node_t *node);
void remove_from_subtree(node_t **node_pp);
u_int8_t remove_str_from_tree(binary_search_tree_t *tree, char *data_str);
void delete_tree(binary_search_tree_t *tree);

#endif // BINARY_SEARCH_TREE_H
