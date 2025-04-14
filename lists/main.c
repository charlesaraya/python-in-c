#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    array_t array;
    init_array(&array, TYPE_INT, 10);

    for (int i = 0; i < 10; i++) {
        append(&array, &i);
    }
    for (int i = 0; i < array.length; i++) {
        printf("Element %d: %d\n", i, ((int *)array.data)[i]);
    }
    free(array.data);
    return 0;
}