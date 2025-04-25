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
    int top;            // Index where the next push goes.
    stack_type_t type;  // Type of list elements
    int type_size;      // Size in bytes of each element
    void *data;         // Pointer to the actual array memory
} pystack_t;


/** @brief Initializes a dynamic stack with given type, and capacity.
 *
 * @param pystack_t Pointer to the stack structure to initialize
 * @param capacity Initial number of elements to allocate
 * @param element_size Size of a single element (in bytes)
 */
error_t init_stack(pystack_t *stack, stack_type_t type, int capacity);


/** @brief Push an element into the stack.
 *
 * @param pystack_t Pointer to the stack structure to initialize
 * @param element Pointer to the element to be pushed into the stack
 */
error_t push(pystack_t *stack, void *element);

/** @brief Pop an element from the stack.
 *
 * @param pystack_t Pointer to the stack to pop from
 */
void *pop(pystack_t *stack);

/** @brief Peek returns the top element without removing it
 *
 * @param pystack_t Pointer to the stack to peef from
 */
void *peek(pystack_t *stack);
