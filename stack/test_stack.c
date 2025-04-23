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
    printf("Test init stack...");
    init_stack(&stack, TYPE_INT, INITIAL_CAPACITY);
    assert(stack.capacity == INITIAL_CAPACITY);
    assert(stack.top == 0);
    assert(stack.type_size == sizeof(int));
    assert(stack.data != NULL);
    printf("[PASSED]\n");

    /** 
     * @name: push
    */
    printf("Test Push... ");
    void *e;
    for (int i = 0; i < 11; i++) {
        push(&stack, &i);
        e = (char *)stack.data + (stack.top - 1) * stack.type_size;
        assert(i == *(int *)e);
    }
    assert(stack.top == 11);
    assert(stack.capacity == 20);
    printf("[PASSED]\n");

    free(stack.data);

    printf("All tests passed.\n");
    return 0;
}