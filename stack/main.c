#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {

    printf("\n===Init===\n");
    pystack_t stack;
    init_stack(&stack, TYPE_INT, 10);

    free(stack.data);
    return 0;
}
