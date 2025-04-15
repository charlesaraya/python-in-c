typedef enum ListType {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_GENERIC,
} list_type_t;

typedef struct List {
    int length;
    int capacity;
    list_type_t type;
    int type_size;
    void *data;
} list_t;

void init_list(list_t *list, list_type_t type, int capacity);

void append(list_t *list, void *element);

void print(list_t *list);
