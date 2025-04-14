#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    list_t list;
    init_list(&list, TYPE_INT, 10);

    for (int i = 0; i < 10; i++) {
        append(&list, &i);
    }
    for (int i = 0; i < list.length; i++) {
        printf("Element %d: %d\n", i, ((int *)list.data)[i]);
    }
    free(list.data);
    return 0;
}