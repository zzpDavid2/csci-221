#include <stdio.h>
#include <limits.h>
#include "binary_search_tree.h"

#define DEBUG 1

order_t compare_str(char *a_str, char *b_str){
    // returns the order_t enum with the result a_str GREATER/LESS (order_t) than b_str
    if(a_str == NULL){
        #if DEBUG == 1
            printf("compare_str failed. a_str is NULL\n");
        #endif
        return LESS;
    }
    if(b_str == NULL){
        #if DEBUG == 1
        printf("compare_str failed. b_str is NULL\n");
        #endif
        return GREATER;
    }
    size_t i = 0;
    do{
        if(a_str[i] > b_str[i]) {
            return GREATER;
        } else if (b_str[i] > a_str[i]) {
            return LESS;
        }
        i++;
        if(i >= SIZE_T_MAX){
            break;
        }
    }while(!(a_str[i]=='\0' || b_str[i]=='\0')); 
    // this is not perfect since we could have a runnaway loop if neither of them have a terminator
    return EQUAL;
}

size_t get_str_len(char *str){
    size_t i = 0;
    while(str[i]!='\0'){
        i++;
        // to prevent an infinite loop.
        if(i >= SIZE_T_MAX){
            break;
        }
    }
    return i;
}

char *copy_str(char *str){
    if(str == NULL){
        #if DEBUG == 1
            printf("copy_str: str is NULL\n");
        #endif
        return NULL;
    }
    size_t length = get_str_len(str);
    char *new_str = calloc(length+1, sizeof(char));
    for(size_t i=0; i<length+1; i++){
        new_str[i] = str[i];
    }
    return new_str;
}

node_t *new_node(char *data_str){
    node_t *node = calloc(1, sizeof(node_t));
    node->data_str = copy_str(data_str); // we need to copy string here because data_str can be immutable.
    return node;
}

binary_search_tree_t *new_bst (char *root_str){
    binary_search_tree_t *bst = calloc(1, sizeof(binary_search_tree_t));
    node_t *root = new_node(root_str);
    bst->root = root;
    bst->size = 1;
    return bst;
}

node_t **find_node_location(node_t **node_pp, char *data_str, size_t *depth){
    // if the depth is NULL, we will not use it to check for infinite recursion
    if(depth != NULL){
        if(depth == 0){
            #if DEBUG == 1
                printf("insert_to_subtree: exceeded maximum depth\n");
            #endif
        return 0;
    }
    }
    if (node_pp == NULL){
        #if DEBUG == 1
            printf("find_node_location: node_pp is NULL\n");
        #endif
        return 0;
    }

    node_t *node = *node_pp;

    if (node == NULL){
        #if DEBUG == 1
            printf("find_node_location: node is NULL\n");
        #endif
        return 0;
    }
    if (data_str == NULL){
        #if DEBUG == 1
            printf("find_node_location: str is NULL\n");
        #endif
        return 0;
    }
    
    order_t order = compare_str(data_str, node->data_str);

    if(order == GREATER){
        if(node->right == NULL){
            return &(node->right);
        }
        if(depth != NULL){
            depth--;
        }
        return find_node_location(&(node->right), data_str, depth);
    }else if (order == LESS){
        if(node->left == NULL){
            return &(node->left);
        }
        if(depth != NULL){
            depth--;
        }
        return find_node_location(&(node->left), data_str, depth);
    }
    #if DEBUG == 1
        printf("find_node_location: duplicate data string\n");
    #endif
    return node_pp;
}

void insert_to_subtree(node_t *node, char *data_str, size_t depth){
    if (node == NULL)
    {
        #if DEBUG == 1
            printf("insert_to_subtree: node is NULL\n");
        #endif
        return;
    }

    if (data_str == NULL){
        #if DEBUG == 1
            printf("insert_to_subtree: str is NULL\n");
        #endif
        return;
    }

    node_t **insert_location = find_node_location(&node, data_str, &depth);
    if (insert_location == NULL){
        #if DEBUG == 1
            printf("insert_to_subtree: insert_location is NULL\n");
        #endif
    }
    if(*insert_location == NULL){
        *insert_location = new_node(data_str);
    }else{
        #if DEBUG == 1
            printf("insert_to_subtree: duplicate data_str\n");
        #endif
    }
    return;
}

void insert(binary_search_tree_t *tree, char *data_str){
    if (tree == NULL)
    {
        #if DEBUG == 1
            printf("insert: tree is NULL\n");
        #endif
        return;
    }
    insert_to_subtree(tree->root, data_str, tree->size);
    tree->size++;
    return;
}

void free_subtree(node_t *node){
    if(node == NULL){
        return;
    }
    if(node->left != NULL){
        free_subtree(node->left);
    }
    if (node->right != NULL){
        free_subtree(node->right);
    }
    free(node->data_str);
    free(node);
    return;
}

void free_node(node_t *node){
    free(node->data_str);
    free(node);
    return;
}

void remove_from_subtree(node_t **node_pp){
    if(node_pp == NULL){
        #if DEBUG == 1
            printf("remove_from_subtree: node_pp is NULL\n");
        #endif
        return;
    }
    node_t *node = *node_pp;
    if(node == NULL){
        #if DEBUG == 1
            printf("remove_from_subtree: *node is NULL\n");
        #endif
        return;
    }

    bool left_is_null = (node->left == NULL);
    bool right_is_null = (node->right == NULL);

    if (left_is_null && right_is_null){
        // remove the node if the node is a leaf
        *node_pp = NULL;
        free_node(node);
        return;
    }else if (left_is_null){
        // replace the node with its right child
        *node_pp = node->right;
        free_node(node);
        return;
    }else if(right_is_null){
        // replace the node with its left child
        *node_pp = node->left;
        free_node(node);
        return;
    }

    // now we need to find the greatest node in the left subtree
    node_t **current_node_pp = &node->left;
    node_t *current_node = node->left;
    while (current_node->right != NULL){
        current_node_pp = &current_node->right;
        current_node = current_node->right;
    }
    // we need to copy str because the original str will be freed
    free(node->data_str);
    node->data_str = copy_str(current_node->data_str);
    remove_from_subtree(current_node_pp);
}

u_int8_t remove_str_from_tree(binary_search_tree_t *tree, char *data_str){
    size_t depth = tree->size;
    node_t **node_pp = find_node_location(&(tree->root), data_str, &depth);
    if(*node_pp == NULL){
        return 0;
    }
    remove_from_subtree(node_pp);
    tree->size--;
    return 1;
}

void delete_tree(binary_search_tree_t *tree){
    free_subtree(tree->root);
    free(tree);
    return;
}
