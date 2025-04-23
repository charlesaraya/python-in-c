#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {
    /** 
     * @name: init_stack
    */
    pystack_t stack;
    const int INITIAL_CAPACITY = 10;
    printf("Test init stack...\n");
    init_stack(&stack, TYPE_INT, INITIAL_CAPACITY);
    assert(stack.capacity == INITIAL_CAPACITY);
    assert(stack.length == 0);
    assert(stack.top == 0);
    assert(stack.type_size == sizeof(int));
    assert(stack.data != NULL);

    free(stack.data);

    printf("All tests passed.\n");
    return 0;
}