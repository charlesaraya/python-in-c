#include "../errors.h"

typedef enum ListType {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_GENERIC,
} list_type_t;

/**
 * @brief A generic dynamic list structure.
 */
typedef struct List {
    int length;         // Current number of elements
    int capacity;       // Total allocated capacity
    list_type_t type;   // Type of list elements
    int type_size;      // Size in bytes of a single element
    void *data;         // Pointer to the actual array memory
} pylist_t;

/** @brief Initializes a dynamic list with given type, and capacity.
 *
 * @param pylist_t Pointer to the array structure to initialize
 * @param capacity Initial number of elements to allocate
 * @param element_size Size of a single element (in bytes)
 */
error_t init_list(pylist_t *list, list_type_t type, int capacity);


/** @brief Returns the length of the list
 *
 * @param pylist_t Pointer to the list structure to initialize
 * @return length of the list
 */
int len(pylist_t *list);

error_t append(pylist_t *list, void *element);

/** @brief Extends a list by appending all the items from another list.
 *
 * @param pylist_t Pointer to the destination list we aim to extend.
 * @param pylist_t Pointer to the source list we aim to extend on destination.
 */
error_t extend(pylist_t *dest_list, pylist_t *src_list);

error_t print(pylist_t *list);

error_t insert(pylist_t *list, void *element, int index);

void *access(pylist_t *list, int index);

void *slice(pylist_t *list, int start, int end, int step);

int in(pylist_t *list, void *element);

void *min(pylist_t *list);

void *max(pylist_t *list);

void *pop(pylist_t *list, int index);

/** @brief Return zero-based index in the list of the first item whose value is equal to element.
 *
 * @param pylist_t Pointer to the list structure to initialize
 * @param element Pointer to the element we aim to find
 * @param start Int used as index to lower limit the search.
 * @param end Int used as index to upper limit the search.
 * @return zero-based index of the found element.
 */
int search_index(pylist_t *list, void *element, int start, int end);


error_t delete(pylist_t *list, void *element);

int count(pylist_t *list, void *element);

/** @brief Reverse the order of a list.
 *
 * @param pylist_t Pointer to the list structure to reverse
 */
error_t reverse(pylist_t *list);
