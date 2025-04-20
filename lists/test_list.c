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
    free(float_list.data);

    /** 
     * @name: min
    */
    int small_num = -100;
    insert(&list, &small_num, 5);
    assert(small_num == *((int *)min(&list)));

    list_t empty_list;
    init_list(&empty_list, TYPE_FLOAT, 10);
    assert(min(&empty_list) == NULL);
    free(empty_list.data);

    /** 
     * @name: max
    */
    int large_num = 500;
    int larger_num = 1000;
    insert(&list, &large_num, 2);
    assert(large_num == *((int *)max(&list)));
    insert(&list, &larger_num, 7);
    int found_max = *((int *)max(&list));
    assert(large_num != found_max);
    assert(larger_num == found_max);

    /** 
     * @name: pop
    */
    int length = list.length;
    int last_item = *(int *)access(&list, -1);
    void *popped = pop(&list, -1);
    assert(*(int *)popped == last_item);
    assert(list.length == length - 1);
    free(popped);

    int first_element = *(int *)access(&list, 0);
    popped = pop(&list, 0);
    assert(*(int *)popped == first_element);
    assert(list.length == length - 2);
    free(popped);

    /** 
     * @name: delete
    */
    length = list.length;
    assert(delete(&list, &small_num) == ERR_OK);
    assert(list.length == length - 1);

    int some_num = -11;
    assert(delete(&list, &some_num) != ERR_OK);
    assert(list.length == length - 1);

    /** 
     * @name: count
    */
    int num = 3;
    insert(&list, &num, 0);
    append(&list, &num);
    assert(count(&list, &num) == 3);
    num = -1;
    assert(count(&list, &num) == 0);


    /** 
     * @name: search_index
    */
   // element found
    int index = search_index(&list, &larger_num, 0, list.length);
    assert(index == 5);
    index = search_index(&list, &larger_num, 3, list.length);
    assert(index == 5);
    index = search_index(&list, &larger_num, 3, list.length + 10);
    assert(index == 5);
    index = search_index(&list, &larger_num, -4, list.length);
    assert(index == 5);
    index = search_index(&list, &larger_num, -list.length, -1);
    assert(index == 5);
    index = search_index(&list, &larger_num, -list.length-10, -1);
    assert(index == 5);
    index = search_index(&list, &larger_num, 3, -1);
    assert(index == 5);
    index = search_index(&list, &larger_num, -list.length, list.length);
    assert(index == 5);
    // element not found
    index = search_index(&list, &larger_num, 5, 5);
    assert(index == -1);
    index = search_index(&list, &larger_num, 0, 3);
    assert(index == -1);
    some_num = -33;
    index = search_index(&list, &some_num, 0, list.length);
    assert(index == -1);

    free(list.data);

    printf("All tests passed.\n");
    return 0;
}