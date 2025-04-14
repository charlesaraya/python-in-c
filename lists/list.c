#include <stdlib.h>
#include <string.h>
#include "list.h"

void init_array(array_t *array, array_type_t type, int capacity) {
    if (NULL == array) {
        return;
    }
    if (capacity <= 0) {
        return;
    }
    switch (type) {
        case TYPE_INT:
            array->type_size = sizeof(int);
            break;
        case TYPE_FLOAT:
            array->type_size = sizeof(float);
            break;
        case TYPE_GENERIC:
            array->type_size = sizeof(void);
            break;
        default:
            return;
    }

    void *data = (void *)malloc(capacity * array->type_size);
    if (NULL == data) {
        return;
    }
    array->data = data;
    array->capacity = capacity;
    array->length = 0;
    array->type = type;
    return;
}

void append(array_t *array, void *element) {
    if (NULL == array || NULL == element) {
        return;
    }
    if (array->length == array->capacity) {
        array->capacity *= 2;
        array->data = realloc(array->data, array->capacity * array->type_size);
        if (NULL == array->data) {
            return;
        }
    }
    void *target = array->data + (array->length * array->type_size);
    memcpy(target, element, array->type_size);
    array->length++;
}