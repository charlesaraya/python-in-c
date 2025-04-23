#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    // Init
    printf("\n===Init===\n");
    pylist_t list;
    init_list(&list, TYPE_INT, 10);
    print(&list);
    printf("len(list): %d\n", len(&list));

    // Append
    printf("\n===Append===\n");
    for (int i = 0; i < 10; i++) {
        append(&list, &i);
    }
    print(&list);
    printf("len(list): %d\n", len(&list));

    // Extend
    printf("\n===Extend===\n");
    pylist_t new_list;
    int aux = 0;
    init_list(&new_list, TYPE_INT, 10);
    for (int i = 0; i < 5; i++) {
        aux = i * i;
        append(&new_list, &aux);
    }
    printf("len(new_list): %d\n", len(&new_list));
    printf("capacity(new_list): %d\n", new_list.capacity);
    print(&new_list);
    extend(&list, &new_list);
    printf("list.extend(new_list):");
    print(&list);
    free(new_list.data);

    // Insert
    printf("\n===Insert===\n");
    int big_num= 100;
    insert(&list, &big_num, 5);
    print(&list);
    big_num= 100*2;
    insert(&list, &big_num, -1);
    print(&list);

    // Access
    printf("\n===Access===\n");
    int *num = (int *)access(&list, 5);
    printf("list[%d]: %d\n", 5, *num);

    num = (int *)access(&list, -1);
    printf("list[%d]: %d\n", -1, *num);

    // Slice
    printf("\n===Slice===\n");
    pylist_t slice_list;
    slice_list = *(pylist_t *)slice(&list, 0, 6, 1);
    printf("list[:6]: ");
    print(&slice_list);
    free(slice_list.data);

    slice_list = *(pylist_t *)slice(&list, 0, list.length, 2);
    printf("list[::2]: ");
    print(&slice_list);
    free(slice_list.data);

    slice_list = *(pylist_t *)slice(&list, 0, list.length, -1);
    printf("list[::-1]: ");
    print(&slice_list);
    free(slice_list.data);

    slice_list = *(pylist_t *)slice(&list, 0, list.length, -2);
    printf("list[::-2]: ");
    print(&slice_list);

    // In
    printf("\n===In===\n");
    print(&list);
    printf("%d in list: %d\n", big_num, in(&list, &big_num));

    float pi = 3.14;
    printf("%f in list: %d\n", pi, in(&list, &pi));

    // Min & Max
    printf("\n===Min & Max===\n");
    print(&list);
    int lowest = *(int *)min(&list);
    int largest = *(int *)max(&list);
    printf("min(list): %d\n", lowest);
    printf("max(list): %d\n", largest);

    // Pop
    printf("\n===Pop===\n");
    print(&list);
    void *popped = pop(&list, 5);
    printf("list.pop(%d): %d\n", 5, *(int *)popped);
    popped = pop(&list, -1);
    printf("list.pop(): %d\n", *(int *)popped);
    print(&list);
    free(popped);

    // Remove
    printf("\n===Remove===\n");
    print(&list);
    int some_num = -100;
    insert(&list, &some_num, 2);
    printf("list.insert(%d, %d)\n", 2, some_num);
    print(&list);
    int result = delete(&list, &some_num);
    printf("list.remove(%d): %d\n", some_num, result);
    some_num = -999;
    printf("list.remove(%d):\n", some_num);
    result = delete(&list, &some_num);
    print(&list);

    // Count
    printf("\n===Count===\n");
    print(&list);
    int num_in_list = 4;
    insert(&list, &num_in_list, 0);
    printf("list.insert(%d, %d)\n", 0, num_in_list);
    insert(&list, &num_in_list, -1);
    printf("list.insert(%d, %d)\n", -1, num_in_list);
    print(&list);
    int counts = count(&list, &num_in_list);    printf("list.count(%d): %d\n", num_in_list, counts);

    int num_not_in_list = -11;
    counts = count(&list, &num_not_in_list);
    printf("list.count(%d): %d\n", num_not_in_list, counts);

    // Index
    printf("\n===Index===\n");
    print(&list);
    some_num = 6;
    int index = search_index(&list, &some_num, 0, list.length);
    printf("list.index(%d): %d\n", some_num, index);
    index = search_index(&list, &some_num, 3, list.length);
    printf("list.index(%d, %d): %d\n", some_num, 3, index);
    index = search_index(&list, &some_num, 3, 5);
    printf("list.index(%d, %d, %d): %d\n", some_num, 3, 5, index);
    index = search_index(&list, &some_num, 3, 10);
    printf("list.index(%d, %d, %d): %d\n", some_num, 3, 10, index);
    index = search_index(&list, &some_num, -4, list.length);
    printf("list.index(%d, %d): %d\n", some_num, -4, index);
    index = search_index(&list, &some_num, -4, -1);
    printf("list.index(%d, %d, %d): %d\n", some_num, -4, -1, index);
    index = search_index(&list, &some_num, -10, -1);
    printf("list.index(%d, %d, %d): %d\n", some_num, -10, -1, index);
    index = search_index(&list, &some_num, 3, -1);
    printf("list.index(%d, %d, %d): %d\n", some_num, 3, -1, index);
    index = search_index(&list, &some_num, -4, 5);
    printf("list.index(%d, %d, %d): %d\n", some_num, -4, 5, index);

    // Reverse
    printf("\n===Reverse===\n");
    print(&list);
    reverse(&list);
    print(&list);

    free(list.data);
    return 0;
}
