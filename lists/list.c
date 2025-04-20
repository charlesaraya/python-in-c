#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

error_t init_list(list_t *list, list_type_t type, int capacity) {
    if (NULL == list) {
        fprintf(stderr, "Error: NULL list_t pointer passed to init_list()\n");
        return ERR_NULL_POINTER;
    }
    if (capacity <= 0) {
        fprintf(stderr, "Error: Negative list_t capacity passed to init_list()\n");
        return ERR_INVALID_ARGUMENT;
    }
    switch (type) {
        case TYPE_INT:
            list->type_size = sizeof(int);
            break;
        case TYPE_FLOAT:
            list->type_size = sizeof(float);
            break;
        case TYPE_GENERIC:
            list->type_size = sizeof(void);
            break;
        default:
            fprintf(stderr, "Error: Unknown list_t type passed to init_list()\n");
            return ERR_INVALID_ARGUMENT;
    }

    void *data = (void *)malloc(capacity * list->type_size);
    if (NULL == data) {
        fprintf(stderr, "Error: Data allocation failed in init_list()\n");
        return ERR_OUT_OF_MEMORY;
    }
    list->data = data;
    list->capacity = capacity;
    list->length = 0;
    list->type = type;
    return ERR_OK;
}

int len(list_t *list) {
    if (NULL == list) {
        fprintf(stderr, "Error: NULL list_t pointer passed to len()\n");
        return ERR_NULL_POINTER;
    }
    return list->length;
}

error_t append(list_t *list, void *element) {
    if (NULL == list || NULL == element) {
        fprintf(stderr, "Error: NULL pointer passed to append()\n");
        return ERR_NULL_POINTER;
    }
    // Double the capacity when full
    if (list->length == list->capacity) {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * list->type_size);
        if (NULL == list->data) {
            fprintf(stderr, "Error: Data allocation failed in append()\n");
            return ERR_OUT_OF_MEMORY;
        }
    }
    void *target = list->data + (list->length * list->type_size);
    memcpy(target, element, list->type_size);
    list->length++;
    return ERR_OK;
}

error_t extend(list_t *dest_list, list_t *src_list) {
    if (NULL == dest_list || NULL == src_list) {
        fprintf(stderr, "Error: NULL pointer passed to extend()\n");
        return ERR_NULL_POINTER;
    }
    if (dest_list->type != src_list->type) {
        fprintf(stderr, "Error: Wrong mismatch in list_t types passed to extend()\n");
        return ERR_TYPE_MISMATCH;
    }
    // Check there's enough capacity on destination  list, otherwise reallocate more memory
    if (dest_list->length + src_list->length > dest_list->capacity) {
        dest_list->capacity = dest_list->length + src_list->length;
        dest_list->data = realloc(dest_list->data, dest_list->capacity * dest_list->type_size);
        if (NULL == dest_list->data) {
            fprintf(stderr, "Error: Data allocation failed in extend()\n");
            return ERR_OUT_OF_MEMORY;
        }
    }
    // get target address at dest list_data where the src list->data will be allocaated
    void *target = (char *)dest_list->data + (dest_list->length * dest_list->type_size);
    memcpy(target, src_list->data, src_list->length * src_list->type_size);
    dest_list->length += src_list->length;
    return ERR_OK;
}

error_t print(list_t *list) {
    if (NULL == list) {
        fprintf(stderr, "Error: NULL pointer passed to print()\n");
        return ERR_NULL_POINTER;
    }
    if (list->length == 0){
        printf("[]\n");
        return ERR_OK;
    }
    printf("[");
    int i = 0;
    while (i < list->length - 1) {
        printf("%d, ", ((int *)list->data)[i]);
        i++;
    } 
    printf("%d", ((int *)list->data)[list->length - 1]);
    printf("]\n");
    return ERR_OK;
}

error_t insert(list_t *list, void *element, int index) {
    if (NULL == list || NULL == element) {
        fprintf(stderr, "Error: NULL pointer passed to insert()\n");
        return ERR_NULL_POINTER;
    }
    void *target = NULL;
    if (index >= list->length || index <= -list->length-1) {
        fprintf(stderr, "Error: Index passed to insert() is out of bounds\n");
        return ERR_INDEX_OUT_OF_BOUNDS;
    } else if (index >= 0) {
        target = list->data + (index * list->type_size);
    } else {
        target = list->data + ((list->length + index) * list->type_size);
    }
    memcpy(target, element, list->type_size);
    return ERR_OK;
}

void *access(list_t *list, int index) {
    if (NULL == list) {
        fprintf(stderr, "Error: NULL pointer passed to access()\n");
        return NULL;
    }
    // Index out of upper and lower bounds
    if (index >= list->length || index <= -list->length-1) {
        fprintf(stderr, "Error: Index passed to access() is out of bounds\n");
        return NULL;
    } else if (index >= 0) {
        void *target = list->data + (index * list->type_size);
        return target;
    } else {
        void *target = list->data + ((list->length + index) * list->type_size);
        return target;
    }
}

int in(list_t *list, void *element) {
    if (NULL == list || NULL == element) {
        fprintf(stderr, "Error: NULL pointer passed to in()\n");
        return ERR_NULL_POINTER;
    }
    for (int i = 0; i < list->length; i++) {
        switch (list->type) {
            case TYPE_INT:
                if ((((int *)list->data)[i]) == *((int *)element)) {
                    return 1;
                }
                break;
            case TYPE_FLOAT:
                if ((((float *)list->data)[i]) == *((float *)element)) {
                    return 1;
                }
                break;
            default:
                fprintf(stderr, "Error: Unknown list_t type passed to in()\n");
                return ERR_INVALID_ARGUMENT;
        }
    }
    return 0;
}

void *min(list_t *list) {
    if (NULL == list) {
        fprintf(stderr, "Error: NULL pointer passed to min()\n");
        return NULL;
    }
    if (list->length == 0) {
        fprintf(stderr, "Error: Invalid argument, empty list passed to min()\n");
        return NULL;
    }
    void *current_min = list->data;
    for (int i = 1; i < list->length; i++) {
        switch (list->type) {
            case TYPE_INT:
                if (((int *)list->data)[i] < *((int *)current_min)) {
                    current_min = (char *)list->data + list->type_size * i;
                }
                break;
            case TYPE_FLOAT:
                if (((float *)list->data)[i] < *((float *)current_min)) {
                    current_min = (char *)list->data + list->type_size * i;
                }
                break;
            default:
                fprintf(stderr, "Error: Unknown list_t type passed to min()\n");
                return NULL;
        }
    }
    return current_min;
}

void *max(list_t *list) {
    if (NULL == list) {
        fprintf(stderr, "Error: NULL pointer passed to max()\n");
        return NULL;
    }
    if (list->length == 0) {
        fprintf(stderr, "Error: Invalid argument, empty list passed to max()\n");
        return NULL;
    }
    void *current_max = list->data;
    for (int i = 1; i < list->length; i++) {
        switch (list->type) {
            case TYPE_INT:
                if (((int *)list->data)[i] > *((int *)current_max)) {
                    current_max = (char *)list->data + list->type_size * i;
                }
                break;
            case TYPE_FLOAT:
                if (((float *)list->data)[i] <= *((float *)current_max)) {
                    current_max = (char *)list->data + list->type_size * i;
                }
                break;
            default:
                fprintf(stderr, "Error: Unknown list_t type passed to max()\n");
                return NULL;
        }
    }
    return current_max;
}

void *pop(list_t *list, int index) {
    if (NULL == list) {
        fprintf(stderr, "Error: NULL pointer passed to pop()\n");
        return NULL;
    }
    if (index < -list->length || index >= list->length) {
        fprintf(stderr, "Error: Index passed to pop() is out of bounds\n");
        return NULL;
    }
    if (index < 0) {
        index = list->length + index;
    }
    void *dest = (char *)list->data + list->type_size * index;
    // Store popped element
    void *popped_element = malloc(list->type_size);
    if (NULL == popped_element) {
        fprintf(stderr, "Error: Data allocation failed in pop()\n");
        return NULL;
    }
    memcpy(popped_element, dest, list->type_size);
    // Shrink list
    size_t num_element = list->length - index - 1;
    memmove(dest, (char *)dest + list->type_size, num_element * list->type_size);
    // Set last element to 0
    list->length--;
    void *last_list_element = (char *)list->data + list->length * list->type_size;
    memset(last_list_element, 0, list->type_size);

    return popped_element;
}

int search_index(list_t *list, void *element, int start, int end) {
    if (NULL == list || NULL == element) {
        fprintf(stderr, "Error: NULL pointer passed to search_index()\n");
        return ERR_NULL_POINTER;
    }
    void *list_element = NULL;
    int index = -1;
    // reset end to the length of the list when out of bounds
    if (end >= list->length) {
        end = list->length;
    }
    // reset start to the length of the list when out of bounds
    if (start < -list->length) {
        start = 0;
    }
    // conversion to positive index
    if (start < 0) {
        start = list->length + start;
    }
    // conversion to positive index
    if (end < 0) {
        end = list->length + end;
    }
    // start must be lower than end
    if (start >= end) {
        return -1;
    }
    // Find the index of the first element in the list matching argument
    for (int i = start; i < end; i++) {
        list_element = (char *)list->data + list->type_size * i;
        switch (list->type) {
            case TYPE_INT:
                if (*(int *)list_element == *(int *)element) {
                    index = i;
                }
                break;
            case TYPE_FLOAT:
                if (*(float *)list_element == *(float *)element) {
                    index = i;
                }
                break;
            default:
                fprintf(stderr, "Error: Unknown list_t type passed to search_index()\n");
                return ERR_INVALID_ARGUMENT;
        }
        // break if an index is found
        if (-1 != index) {
            break;
        }
    }
    return index;
}

error_t delete(list_t *list, void *element) {
    if (NULL == list || NULL == element) {
        fprintf(stderr, "Error: NULL pointer passed to delete()\n");
        return ERR_NULL_POINTER;
    }
    void *list_element = NULL;
    int index = -1;
    // Find the index of the first element in the list matching argument
    for (int i = 0; i < list->length; i++) {
        list_element = (char *)list->data + list->type_size * i;
        switch (list->type) {
            case TYPE_INT:
                if (*(int *)list_element == *(int *)element) {
                    index = i;
                }
                break;
            case TYPE_FLOAT:
                if (*(float *)list_element == *(float *)element) {
                    index = i;
                }
                break;
            default:
                fprintf(stderr, "Error: Unknown list_t type passed to delete()\n");
                return ERR_INVALID_ARGUMENT;
                break;
        }
        // break if an index is found
        if (-1 != index) {
            break;
        }
    }
    // element not found in the list
    if (-1 == index) {
        fprintf(stderr, "Error: Element passed to delete() not found in list\n");
        return ERR_NOT_FOUND;
    }
    // element found, hence shrink the list at index
    void *dest = (char *)list->data + list->type_size * index;
    size_t shift_length = list->length - index - 1;
    memmove(dest, (char *)dest + list->type_size, shift_length * list->type_size);
    // Set last element to 0
    list->length--;
    void *last_list_element = (char *)list->data + list->length * list->type_size;
    memset(last_list_element, 0, list->type_size);
    return ERR_OK;
}

int count(list_t *list, void *element) {
    if (NULL == list || NULL == element) {
        fprintf(stderr, "Error: NULL pointer passed to count()\n");
        return ERR_NULL_POINTER;
    }
    void *list_element = NULL;
    int count = 0;
    for (int i = 0; i < list->length; i++) {
        list_element = (char *)list->data + list->type_size * i;
        switch (list->type) {
            case TYPE_INT:
                if (*(int *)list_element == *(int *)element) {
                    count++;
                }
                break;
            case TYPE_FLOAT:
                if (*(float *)list_element == *(float *)element) {
                    count++;
                }
                break;
            default:
                fprintf(stderr, "Error: Unknown list_t type passed to count()\n");
                return ERR_INVALID_ARGUMENT;
        }
    }
    return count;
}

error_t reverse(list_t *list) {
    if (NULL == list) {
        fprintf(stderr, "Error: NULL pointer passed to reverse()\n");
        return ERR_NULL_POINTER;
    }
    if (list->length < 2) {
        return ERR_OK;
    }
    void *head = NULL;
    void *tail = NULL;
    // Allocate a temp buffer for generic type swap.
    void *temp = malloc(list->type_size);
    if (NULL == temp) {
        fprintf(stderr, "Error: Data allocation failed in reverse()\n");
        return ERR_OUT_OF_MEMORY;
    }
    for (int i = 0; i < list->length / 2; i++) {
        head = list->data + list->type_size * i;
        tail = list->data + list->type_size * (list->length - 1 - i);
        memcpy(temp, head, list->type_size);
        memcpy(head, tail, list->type_size);
        memcpy(tail, temp, list->type_size);
    }
    free(temp);
    return ERR_OK;
}
