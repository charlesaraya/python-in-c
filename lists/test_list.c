#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    /** 
     * @name: init_list
    */
    list_t list;
    const int INITIAL_CAPACITY = 10;
    printf("Test init list...\n");
    init_list(&list, TYPE_INT, INITIAL_CAPACITY);
    assert(list.capacity == INITIAL_CAPACITY);
    assert(list.length == 0);
    assert(list.type_size == sizeof(int));
    assert(list.data != NULL);

    /** 
     * @name: len
    */
    assert(list.length == len(&list));

    /** 
     * @name: append
    */
    printf("Test append...\n");
    for (int i = 0; i < INITIAL_CAPACITY + 1; i++) {
        append(&list, &i);
    }
    assert(list.capacity == INITIAL_CAPACITY * 2);
    assert(list.length == INITIAL_CAPACITY + 1);
    assert(list.data != NULL);


    free(list.data);

    printf("All tests passed.\n");
    return 0;
}