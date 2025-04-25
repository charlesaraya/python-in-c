#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

const int TOTAL_PUSHED = 11;
const int TOTAL_POPPED = 4;

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
    for (int i = 0; i < TOTAL_PUSHED; i++) {
        push(&stack, &i);
        e = (char *)stack.data + (stack.top - 1) * stack.type_size;
        assert(i == *(int *)e);
    }
    assert(stack.top == TOTAL_PUSHED);
    assert(stack.capacity == 20);
    printf("[PASSED]\n");

    /** 
     * @name: pop
    */
    printf("Test Pop... ");
    void *p;
    for (int i = 0; i < TOTAL_POPPED; i++) {
        p = pop(&stack);
        assert(TOTAL_PUSHED - 1 - i == *(int *)p);
    }
    assert(stack.top == TOTAL_PUSHED - TOTAL_POPPED);

    // Test Pop from empty stack
    pystack_t empty_stack;
    init_stack(&empty_stack, TYPE_INT, 1);
    p = pop(&empty_stack);
    assert(NULL == p);
    free(p);
    printf("[PASSED]\n");

    /** 
     * @name: peek
    */
    printf("Test Peek... ");
    p = peek(&stack);
    assert(TOTAL_PUSHED - TOTAL_POPPED - 1 == *(int *)p);

    // Peer an empty stack
    p = peek(&empty_stack);
    assert(NULL == p);
    free(p);
    free(empty_stack.data);
    printf("[PASSED]\n");

    free(stack.data);

    printf("All tests passed.\n");
    return 0;
}