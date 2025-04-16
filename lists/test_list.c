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

    /** 
     * @name: in
    */
    printf("Test in...\n");
    int in_list = 9;
    int not_in_list = 100;
    assert(in(&list, &in_list) == 1);
    assert(in(&list, &not_in_list) == 0);

    list_t float_list;
    init_list(&float_list, TYPE_FLOAT, INITIAL_CAPACITY);
    float pi = 3.14;
    float e = 2.71;
    append(&float_list, &pi);
    assert(in(&float_list, &pi) == 1);
    assert(in(&float_list, &e) == 0);

    free(list.data);

    printf("All tests passed.\n");
    return 0;
}