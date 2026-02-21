#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define DEBUG 1

typedef struct node_t {
    uint32_t data_value;
    struct node_t *next_node;
} node_t;

typedef struct linked_list_t {
    size_t size;
    node_t *first_node;
} linked_list_t;

node_t *get_node(linked_list_t* list, size_t index){
    node_t *current_node = list->first_node;
    for(size_t i=0; i<index; i++){
        if(current_node != NULL){
            current_node = current_node->next_node;
        }else{
            #if DEBUG == 1
                printf("get_node failed. current_node is NULL.\n");
            #endif
            return NULL;
        }
    }
    return current_node;
}

node_t *new_node(uint32_t value){
    node_t *new_node = calloc(1, sizeof(node_t));
    new_node->data_value = value;
    new_node->next_node = NULL;
    return new_node;
}

void append_to_list(linked_list_t* list, uint32_t value){
    node_t *last_node = get_node(list, list->size-1);

    if (last_node != NULL){
        last_node->next_node = new_node(value);
        list->size++;
    } else {
        #if DEBUG == 1
            printf("Append failed. last_node is NULL.\n");
        #endif
    }

    return;
}

linked_list_t *new_list(size_t size, int32_t initial_value){
    linked_list_t *new_list = calloc(1, sizeof(linked_list_t));
    new_list->size = size;
    node_t **current_node_pp = &(new_list->first_node);
    for (size_t i = 0; i < size; i++){   
        *current_node_pp = new_node(initial_value);
        current_node_pp = &((*current_node_pp)->next_node);
    }
    return new_list;
}

node_t *delete_node(node_t **node){
    if (*node != NULL){
        if ((*node)->next_node == NULL){
            free(*node);
            *node = NULL;
            return NULL;
        }
        node_t *temp_node = *node;
        *node = (*node)->next_node;
        free(temp_node);
    } else {
        #if DEBUG == 1
            printf("Delete failed. node is NULL.\n");
        #endif
    }
    return *node;
}

uint32_t delete_value_from_list(linked_list_t *list, uint32_t value){
    if(list == NULL){
        #if DEBUG == 1
            printf("delete_value_from_list failed. list is NULL.\n");
        #endif
        return 0;
    }
    
    node_t **current_node = &(list->first_node);
    uint32_t count = 0;
    
    while (*current_node != NULL){
        if ((*current_node)->data_value == value){
            delete_node(current_node);
            count++;
            list->size--;
        }else{
            current_node = &((*current_node)->next_node);
        }

    }
    return count;
}

void delete_list(linked_list_t *list){
    node_t *current_node = list->first_node;
    while (current_node != NULL){
        node_t *temp_node = current_node;
        current_node = current_node->next_node;
        free(temp_node);
    }
    free(list);
}

int *remove_odds(int *array, size_t size){
    if(array == NULL){
        #if DEBUG == 1
            printf("remove_odds failed. array is NULL.\n");
        #endif
        return NULL;
    }
    int *new_array = calloc(size, sizeof(int));
    new_array[0] = 0;
    size_t new_size = 0;
    for (size_t i = 0; i < size; i++){
        if (array[i] % 2 == 0){
            new_array[new_size] = array[i];
            new_size++;
        }
    }
    return new_array;
}

char *find_char(char *string, char target){
    if (string == NULL){
        #if DEBUG == 1
            printf("find_char failed. string is NULL.\n");
        #endif
        return NULL;
    }
    while (*string != '\0'){
        if (*string == target){
            return string;
        }
        string++;
    }
    return NULL;
}

size_t get_string_length(char *string){
    if (string == NULL){
        #if DEBUG == 1
            printf("get_string_length failed. string is NULL.\n");
        #endif
        return 0;
    }
    char *start = string;
    while (*string != '\0'){
        string++;
    }
    return string - start;
}

int main(int argc, char *argv[]) {
    linked_list_t *list = new_list(10, 2);
    for (size_t i = 0; i < 10; i++)
    {
        printf("%d", get_node(list, 9)->data_value);
    }
    append_to_list(list, 4);
    printf("%d\n", get_node(list, 10)->data_value);

    delete_value_from_list(list, 2);
    printf("%zu\n", list->size);

    delete_list(new_list(20, 4));

    int test_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *new_array = remove_odds(test_array, 10);

    for (size_t i = 0; i < 10; i++){
        printf("%d ", new_array[i]);
    }

    char *found_char = find_char("Hello, World!", 'o');
    if (found_char != NULL) {
        printf("\nFound character %c\n", *found_char);
    }

    printf("String length: %zu\n", get_string_length("Hello, World!"));

    printf("Please input a character to use as separator\n");
    char separator;
    scanf("%c", &separator);

    for (int32_t i = 0; i < argc; i++)
    {
        printf("%s%c", argv[i], separator);
    }

    return 0;
}
