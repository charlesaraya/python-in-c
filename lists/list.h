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
void init_list(list_t *list, list_type_t type, int capacity);


/** @brief Returns the length of the list
 *
 * @param list_t Pointer to the list structure to initialize
 * @return length of the list
 */
int len(list_t *list);

void append(list_t *list, void *element);

void print(list_t *list);

void insert(list_t *list, void *element, int index);

void *access(list_t *list, int index);

int in(list_t *list, void *element);

void *min(list_t *list);

void *max(list_t *list);

void *pop(list_t *list, int index);

int delete(list_t *list, void *element);
