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
    int length;         ///< Current number of elements
    int capacity;       ///< Total allocated capacity
    list_type_t type;   ///< Type of list elements
    int type_size;      ///< Size in bytes of a single element
    void *data;         ///< Pointer to the actual array memory
} list_t;

/** @brief Initializes a dynamic list with given type, and capacity.
 *
 * @param list_t Pointer to the array structure to initialize
 * @param capacity Initial number of elements to allocate
 * @param element_size Size of a single element (in bytes)
 */
error_t init_list(list_t *list, list_type_t type, int capacity);


/** @brief Returns the length of the list
 *
 * @param list_t Pointer to the list structure to initialize
 * @return length of the list
 */
int len(list_t *list);

error_t append(list_t *list, void *element);

/** @brief Extends a list by appending all the items from another list.
 *
 * @param list_t Pointer to the destination list we aim to extend.
 * @param list_t Pointer to the source list we aim to extend on destination.
 */
error_t extend(list_t *dest_list, list_t *src_list);

error_t print(list_t *list);

error_t insert(list_t *list, void *element, int index);

void *access(list_t *list, int index);

int in(list_t *list, void *element);

void *min(list_t *list);

void *max(list_t *list);

void *pop(list_t *list, int index);

/** @brief Return zero-based index in the list of the first item whose value is equal to element.
 *
 * @param list_t Pointer to the list structure to initialize
 * @param element Pointer to the element we aim to find
 * @param start Int used as index to lower limit the search.
 * @param end Int used as index to upper limit the search.
 * @return zero-based index of the found element.
 */
int search_index(list_t *list, void *element, int start, int end);


error_t delete(list_t *list, void *element);

int count(list_t *list, void *element);

/** @brief Reverse the order of a list.
 *
 * @param list_t Pointer to the list structure to reverse
 */
error_t reverse(list_t *list);
