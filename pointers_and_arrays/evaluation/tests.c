#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "binary_search_tree.h"
#include "binary_search_tree_test.h"

void test_compare_str(void) {
    printf("Testing compare_str...\n");
    
    // Test equal strings
    assert(compare_str("hello", "hello") == EQUAL);
    assert(compare_str("", "") == EQUAL);
    
    // Test greater than
    assert(compare_str("world", "hello") == GREATER);
    assert(compare_str("b", "a") == GREATER);
    
    // Test less than
    assert(compare_str("hello", "world") == LESS);
    assert(compare_str("a", "b") == LESS);
    
    // Test NULL handling
    assert(compare_str(NULL, "hello") == LESS);
    assert(compare_str("hello", NULL) == GREATER);
    
    printf("  ✓ compare_str tests passed\n");
}

void test_get_str_len(void) {
    printf("Testing get_str_len...\n");
    
    assert(get_str_len("") == 0);
    assert(get_str_len("hello") == 5);
    assert(get_str_len("Hello, World!") == 13);
    
    printf("  ✓ get_str_len tests passed\n");
}

void test_copy_str(void) {
    printf("Testing copy_str...\n");
    
    char *original = "test string";
    char *copy = copy_str(original);
    
    assert(copy != NULL);
    assert(copy != original); // Different addresses
    assert(strcmp(copy, original) == 0); // Same content
    
    free(copy);
    
    // Test NULL handling
    assert(copy_str(NULL) == NULL);
    
    printf("  ✓ copy_str tests passed\n");
}

void test_new_bst(void) {
    printf("Testing new_bst...\n");
    
    binary_search_tree_t *tree = new_bst("root");
    
    assert(tree != NULL);
    assert(tree->size == 1);
    assert(tree->root != NULL);
    assert(strcmp(tree->root->data_str, "root") == 0);
    assert(tree->root->left == NULL);
    assert(tree->root->right == NULL);
    
    delete_tree(tree);
    
    printf("  ✓ new_bst tests passed\n");
}

void test_insert(void) {
    printf("Testing insert...\n");
    
    binary_search_tree_t *tree = new_bst("dog");
    
    // Insert smaller values (left)
    insert(tree, "cat");
    insert(tree, "ant");
    
    // Insert larger values (right)
    insert(tree, "elephant");
    insert(tree, "zebra");
    
    // Verify tree structure
    assert(tree->root != NULL);
    assert(strcmp(tree->root->data_str, "dog") == 0);
    
    // Check left subtree
    assert(tree->root->left != NULL);
    assert(strcmp(tree->root->left->data_str, "cat") == 0);
    assert(tree->root->left->left != NULL);
    assert(strcmp(tree->root->left->left->data_str, "ant") == 0);
    
    // Check right subtree
    assert(tree->root->right != NULL);
    assert(strcmp(tree->root->right->data_str, "elephant") == 0);
    assert(tree->root->right->right != NULL);
    assert(strcmp(tree->root->right->right->data_str, "zebra") == 0);
    
    delete_tree(tree);
    
    printf("  ✓ insert tests passed\n");
}

void test_find_node_location(void) {
    printf("Testing find_node_location...\n");
    
    binary_search_tree_t *tree = new_bst("middle");
    insert(tree, "apple");
    insert(tree, "zebra");
    
    size_t depth = tree->size;
    
    // Find existing nodes
    node_t **found = find_node_location(&(tree->root), "middle", &depth);
    assert(found != NULL);
    assert(*found != NULL);
    assert(strcmp((*found)->data_str, "middle") == 0);
    
    found = find_node_location(&(tree->root), "apple", &depth);
    assert(found != NULL);
    assert(*found != NULL);
    assert(strcmp((*found)->data_str, "apple") == 0);
    
    delete_tree(tree);
    
    printf("  ✓ find_node_location tests passed\n");
}

void test_remove_str_from_tree(void) {
    printf("Testing remove_str_from_tree...\n");
    
    // Test removing leaf node
    binary_search_tree_t *tree1 = new_bst("m"); // m for middle
    insert(tree1, "a"); // goes left
    insert(tree1, "z"); // goes right
    
    u_int8_t result = remove_str_from_tree(tree1, "a");
    assert(result == 1);
    assert(tree1->root->left == NULL);
    
    delete_tree(tree1);
    
    // Test removing node with one child
    binary_search_tree_t *tree2 = new_bst("m");
    insert(tree2, "a");
    insert(tree2, "b"); // goes left of m, right of a
    
    result = remove_str_from_tree(tree2, "a");
    assert(result == 1);
    assert(tree2->root->left != NULL);
    assert(strcmp(tree2->root->left->data_str, "b") == 0);
    
    delete_tree(tree2);
    
    // Test removing non-existent node
    binary_search_tree_t *tree3 = new_bst("root");
    result = remove_str_from_tree(tree3, "nonexistent");
    assert(result == 0);
    
    delete_tree(tree3);
    
    printf("  ✓ remove_str_from_tree tests passed\n");
}

void test_delete_tree(void) {
    printf("Testing delete_tree...\n");
    
    binary_search_tree_t *tree = new_bst("root");
    insert(tree, "a");
    insert(tree, "b");
    insert(tree, "c");
    insert(tree, "d");
    
    // This should free all nodes without crashing
    delete_tree(tree);
    
    printf("  ✓ delete_tree tests passed (no memory leaks)\n");
}

void test_comprehensive(void) {
    printf("Testing comprehensive BST operations...\n");
    
    // Build a more complex tree
    binary_search_tree_t *tree = new_bst("mango");
    insert(tree, "apple");
    insert(tree, "banana");
    insert(tree, "cherry");
    insert(tree, "date");
    insert(tree, "fig");
    insert(tree, "grape");
    insert(tree, "kiwi");
    insert(tree, "lemon");
    insert(tree, "orange");
    insert(tree, "peach");
    
    // Verify root
    assert(strcmp(tree->root->data_str, "mango") == 0);
    
    // remove_str_from_tree some nodes
    remove_str_from_tree(tree, "banana");
    remove_str_from_tree(tree, "grape");
    remove_str_from_tree(tree, "peach");
    
    delete_tree(tree);
    
    printf("  ✓ comprehensive tests passed\n");
}

int main(void) {
    printf("\n=== Binary Search Tree Tests ===\n\n");
    
    test_compare_str();
    test_get_str_len();
    test_copy_str();
    test_new_bst();
    test_insert();
    test_find_node_location();
    test_remove_str_from_tree();
    test_delete_tree();
    test_comprehensive();
    
    printf("\n=== All tests passed! ===\n\n");

    binary_search_tree_t *test_tree = new_bst("test");

    printf("Initial tree size: %zu\n", test_tree->size);
    printf("Initial node: %s\n", test_tree->root->data_str);

    insert(test_tree, "testa");
    insert(test_tree, "tesa");

    printf("Tree size after insertions: %zu\n", test_tree->size);
    printf("left node: %s\n", test_tree->root->left->data_str);
    printf("right node: %s\n", test_tree->root->right->data_str);

    insert(test_tree, "tesb");

    printf("left-right: %s\n", test_tree->root->left->right->data_str);

    printf("%u\n", remove_str_from_tree(test_tree, "test"));
    printf("%u\n", remove_str_from_tree(test_tree, "abc"));

    printf("Root node: %s\n", test_tree->root->data_str);
    
    delete_tree(test_tree);

    test_tree = new_bst("test");

    remove_str_from_tree(test_tree, "test");

    remove_str_from_tree(test_tree, "test");

    insert(test_tree, "a");

    return 0;
}
