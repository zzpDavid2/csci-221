#ifndef BINARY_SEARCH_TREE_TEST_H
#define BINARY_SEARCH_TREE_TEST_H

#include "binary_search_tree.h"

// Internal helper functions exposed for testing only

// string helpers

// get_str_len: Returns length of null-terminated string
size_t get_str_len(char *str);

// compare_str: Returns comparison result (GREATER, EQUAL, LESS)
order_t compare_str(char *a_str, char *b_str);

// copy_str: Returns copy of input string
char *copy_str(char *str);

// bst helpers

// find_node_location: Recursively finds where string should be in tree; returns pointer-to-pointer for parent link updates
node_t **find_node_location(node_t **node_pp, char *data_str, size_t *depth);

// insert_to_subtree: Internal function to insert into subtree; used by insert()
void insert_to_subtree(node_t *node, char *data_str, size_t depth);

// free_node: Frees single node only (preserves children)
void free_node(node_t *node);

// remove_from_subtree: Removes node; handles leaf, one child, and two child cases
void remove_from_subtree(node_t **node_pp);

#endif // BINARY_SEARCH_TREE_TEST_H
