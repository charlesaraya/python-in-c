#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

error_t init_stack(pystack_t *stack, stack_type_t type, int capacity) {
    if (NULL == stack) {
        fprintf(stderr, "Error: NULL stack_t pointer passed to init_stack()\n");
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
            fprintf(stderr, "Error: Unknown stack_t type passed to init_stack()\n");
            return ERR_INVALID_ARGUMENT;
    }

    void *data = (void *)malloc(capacity * stack->type_size);
    if (NULL == data) {
        fprintf(stderr, "Error: Data allocation failed in init_stack()\n");
        return ERR_OUT_OF_MEMORY;
    }
    stack->capacity = capacity;
    stack->length = 0;
    stack->top = 0;
    stack->type = type;
    stack->data = data;
    return ERR_OK;
}
