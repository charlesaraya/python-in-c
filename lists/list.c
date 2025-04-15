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

void append(list_t *list, void *element) {
    if (NULL == list || NULL == element) {
        return;
    }
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

void print(list_t *list) {
    if (NULL == list) {
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
