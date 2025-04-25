#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {

    printf("\n===Init===\n");
    pystack_t stack;
    init_stack(&stack, TYPE_INT, 10);

    printf("\n===Push===\n");
    for (int i = 0; i < 11; i++) {
        push(&stack, &i);
        void *e = (char *)stack.data + (stack.top - 1) * stack.type_size;
        printf("Push(%d) ", *(int *)e);
    }
    printf("\nCapacity: %d\n", stack.capacity);
    printf("Top: %d\n", stack.top);

    printf("\n===Pop===\n");
    void *p;
    for (int i = 0; i < 4; i++) {
        p = pop(&stack);
        printf("Pop: %d ", *(int *)p);
    }
    printf("\nCapacity: %d\n", stack.capacity);
    printf("Top: %d\n", stack.top);
    free(p);

    printf("\n===Peek===\n");
    p = peek(&stack);
    printf("Peek: %d\n", *(int *)p);
    printf("Top: %d\n", stack.top);
    free(p);

    free(stack.data);
    return 0;
}
