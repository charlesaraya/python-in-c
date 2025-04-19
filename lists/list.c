#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

void init_list(list_t *list, list_type_t type, int capacity) {
    if (NULL == list) {
        return;
    }
    if (capacity <= 0) {
        return;
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
            return;
    }

    void *data = (void *)malloc(capacity * list->type_size);
    if (NULL == data) {
        return;
    }
    list->data = data;
    list->capacity = capacity;
    list->length = 0;
    list->type = type;
    return;
}

int len(list_t *list) {
    if (NULL == list) {
        return -1;
    }
    return list->length;
}

void append(list_t *list, void *element) {
    if (NULL == list || NULL == element) {
        return;
    }
    // Double the capacity when full
    if (list->length == list->capacity) {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * list->type_size);
        if (NULL == list->data) {
            return;
        }
    }
    void *target = list->data + (list->length * list->type_size);
    memcpy(target, element, list->type_size);
    list->length++;
}

void extend(list_t *dest_list, list_t *src_list) {
    if (NULL == dest_list || NULL == src_list || dest_list->type != src_list->type) {
        return;
    }
    // Check there's enough capacity on destination  list, otherwise reallocate more memory
    if (dest_list->length + src_list->length > dest_list->capacity) {
        dest_list->capacity = dest_list->length + src_list->length;
        dest_list->data = realloc(dest_list->data, dest_list->capacity * dest_list->type_size);
        if (NULL == dest_list->data) {
            return;
        }
    }
    // get target address at dest list_data where the src list->data will be allocaated
    void *target = (char *)dest_list->data + (dest_list->length * dest_list->type_size);
    memcpy(target, src_list->data, src_list->length * src_list->type_size);
    dest_list->length += src_list->length;
    return;
}

void print(list_t *list) {
    if (NULL == list) {
        return;
    }
    if (list->length == 0){
        printf("[]\n");
        return;
    }
    printf("[");
    int i = 0;
    while (i < list->length - 1) {
        printf("%d, ", ((int *)list->data)[i]);
        i++;
    } 
    printf("%d", ((int *)list->data)[list->length - 1]);
    printf("]\n");
}

void insert(list_t *list, void *element, int index) {
    if (NULL == list) {
        return;
    }
    void *target = NULL;
    if (index >= list->length || index <= -list->length-1) {
        return;
    } else if (index >= 0) {
        target = list->data + (index * list->type_size);
    } else {
        target = list->data + ((list->length + index) * list->type_size);
    }
    memcpy(target, element, list->type_size);
}

void *access(list_t *list, int index) {
    if (NULL == list) {
        return NULL;
    }
    // Index out of upper and lower bounds
    if (index >= list->length || index <= -list->length-1) {
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
        return -1;
    }
    for (int i = 0; i < list->length; i++) {
        switch (list->type) {
            case TYPE_INT:
                if ((((int *)list->data)[i]) == *((int *)element)) { return 1; }
            case TYPE_FLOAT:
                if ((((float *)list->data)[i]) == *((float *)element)) { return 1; }
            default:
                break;
        }
    }
    return 0;
}

void *min(list_t *list) {
    if (NULL == list || list->length == 0) {
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
                break;
        }
    }
    return current_min;
}

void *max(list_t *list) {
    if (NULL == list || list->length == 0) {
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
                break;
        }
    }
    return current_max;
}

void *pop(list_t *list, int index) {
    if (NULL == list || index < -list->length || index >= list->length) {
        return NULL;
    }
    if (index < 0) {
        index = list->length + index;
    }
    void *dest = (char *)list->data + list->type_size * index;
    // Store popped element
    void *popped_element = malloc(list->type_size);
    if (NULL == popped_element) {
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
    void *list_element = NULL;
    int index = -1;
    if (NULL == list || NULL == element) {
        return -1;
    }
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
                break;
        }
        // break if an index is found
        if (-1 != index) {
            break;
        }
    }
    return index;
}

int delete(list_t *list, void *element) {
    void *list_element = NULL;
    int index = -1;

    if (NULL == list || NULL == element) {
        return -1;
    }
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
                break;
        }
        // break if an index is found
        if (-1 != index) {
            break;
        }
    }
    // element not found in the list
    if (-1 == index) {
        return 0;
    }
    // element found, hence shrink the list at index
    void *dest = (char *)list->data + list->type_size * index;
    size_t shift_length = list->length - index - 1;
    memmove(dest, (char *)dest + list->type_size, shift_length * list->type_size);
    // Set last element to 0
    list->length--;
    void *last_list_element = (char *)list->data + list->length * list->type_size;
    memset(last_list_element, 0, list->type_size);
    return 1;
}

int count(list_t *list, void *element) {
    void *list_element = NULL;
    int count = 0;

    if (NULL == list || NULL == element) {
        return -1;
    }
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
                break;
        }
    }
    return count;
}
