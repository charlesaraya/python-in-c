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

    int big_num= 100;
    insert(&list, &big_num, 5);
    print(&list);

    free(list.data);
    return 0;
}
