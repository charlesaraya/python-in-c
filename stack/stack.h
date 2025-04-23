#include "../errors.h"

/**
 * @brief An enum to keep track of supported types
 */
typedef enum StackType {
    TYPE_INT,
    TYPE_FLOAT,
} stack_type_t;


/**
 * @brief A generic dynamic stack data structure.
 */
typedef struct Stack {
    int capacity;       // Total allocated capacity
    int length;         // Total number of elements in the stack
    int top;            // Index where the next push goes.
    stack_type_t type;  // Type of list elements
    int type_size;      // Size in bytes of each element
    void *data;         // Pointer to the actual array memory
} pystack_t;


/** @brief Initializes a dynamic stack with given type, and capacity.
 *
 * @param list_t Pointer to the array structure to initialize
 * @param capacity Initial number of elements to allocate
 * @param element_size Size of a single element (in bytes)
 */
error_t init_stack(pystack_t *stack, stack_type_t type, int capacity);