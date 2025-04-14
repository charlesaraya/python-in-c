typedef enum ArrayType {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_GENERIC,
} array_type_t;

typedef struct Array {
    int length;
    int capacity;
    array_type_t type;
    int type_size;
    void *data;
} array_t;

void init_array(array_t *array, array_type_t type, int capacity);

void append(array_t *from_array, void *element);
