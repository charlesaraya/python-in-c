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

    free(list.data);
    return 0;
}
