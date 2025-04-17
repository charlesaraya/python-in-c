#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    list_t list;
    init_list(&list, TYPE_INT, 10);

    for (int i = 0; i < 10; i++) {
        append(&list, &i);
    }
    print(&list);
    printf("Length: %d\n", len(&list));

    // Insert
    int big_num= 100;
    insert(&list, &big_num, 5);
    print(&list);
    big_num= 100*2;
    insert(&list, &big_num, -1);
    print(&list);

    // Access
    int *num = (int *)access(&list, 5);
    printf("%d\n", *num);

    num = (int *)access(&list, -1);
    printf("%d\n", *num);

    // In
    int is_found = in(&list, &big_num);
    if (is_found == 1) { printf("%d Found\n", big_num); } else if (is_found == 0) { printf("%d Not Found\n", big_num); } 

    float pi = 3.14;
    is_found = in(&list, &pi);
    if (is_found == 1) { printf("%f Found\n", pi); } else if (is_found == 0) { printf("%f Not Found\n", pi); } 

    // Min
    int negative = -100;
    append(&list, &negative);
    void *lowest = min(&list);
    printf("Min: %d\n", *(int *)lowest);

    // Max
    int very_big_num = 1000;
    insert(&list, &very_big_num, 3);
    int largest = *((int *)max(&list));
    printf("Max: %d\n", largest);

    // Pop
    printf("\n===Pop===\n");
    print(&list);
    void *popped = pop(&list, 5);
    printf("Pop(%d): %d\n", 5, *(int *)popped);
    popped = pop(&list, -2);
    printf("Pop(%d): %d\n", -2, *(int *)popped);
    print(&list);
    free(popped);

    // Remove
    int remove_this_num = -100;
    printf("Pre-Remove\n");
    print(&list);
    int result = delete(&list, &remove_this_num);
    if (0 == result) {
        printf("Element %d found\n", remove_this_num);
    } else if (1 == result) {
        printf("Element %d not found\n", remove_this_num);
    }
    printf("Post-Remove\n");
    print(&list);

    free(list.data);
    return 0;
}
