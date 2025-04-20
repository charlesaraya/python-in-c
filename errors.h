#ifndef ERRORS_H
#define ERRORS_H

typedef enum ErrorType {
    ERR_OK = 0,                  // Operation completed successfully
    ERR_NULL_POINTER,            // A pointer was unexpectedly NULL
    ERR_OUT_OF_MEMORY,           // Memory allocation failed
    ERR_TYPE_MISMATCH,           // Types did not match
    ERR_INDEX_OUT_OF_BOUNDS,     // Accessed invalid index
    ERR_INVALID_ARGUMENT,        // Invalid argument
    ERR_NOT_FOUND,                // Element not found
} error_t;

#endif