#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

error_t init_stack(pystack_t *stack, stack_type_t type, int capacity) {
    if (NULL == stack) {
        fprintf(stderr, "Error: NULL pystack_t pointer passed to init_stack()\n");
        return ERR_NULL_POINTER;
    }
    if (capacity <= 0) {
        fprintf(stderr, "Error: Invalid capacity argument passed to init_stack(). Must greater than 0.\n");
        return ERR_INVALID_ARGUMENT;
    }
    // Assign stack type
    switch (type) {
        case TYPE_INT:
            stack->type_size = sizeof(int);
            break;
        case TYPE_FLOAT:
            stack->type_size = sizeof(float);
            break;
        default:
            fprintf(stderr, "Error: Unknown pystack_t type passed to init_stack()\n");
            return ERR_INVALID_ARGUMENT;
    }

    void *data = (void *)malloc(capacity * stack->type_size);
    if (NULL == data) {
        fprintf(stderr, "Error: Data allocation failed in init_stack()\n");
        return ERR_OUT_OF_MEMORY;
    }
    stack->capacity = capacity;
    stack->top = 0;
    stack->type = type;
    stack->data = data;
    return ERR_OK;
}


error_t push(pystack_t *stack, void *element) {
    if (NULL == stack) {
        fprintf(stderr, "Error: NULL pystack_t pointer passed to push()");
        return ERR_NULL_POINTER;
    }
    if (NULL == element) {
        fprintf(stderr, "Error: NULL element pointer passed to push()");
        return ERR_NULL_POINTER;
    }
    if (stack->top == stack->capacity) {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, stack->capacity);
        if (NULL == stack->data) {
            fprintf(stderr, "Error: Reallocation failed in push()");
            return ERR_OUT_OF_MEMORY;
        }
    }
    void *target = (char *)stack->data + stack->top * stack->type_size;
    memcpy(target, element, stack->type_size);
    stack->top++;
    return ERR_OK;
}
