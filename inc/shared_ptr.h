#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include <stdlib.h>

#define shared_ptr(TYPE) __attribute__((cleanup(destructor_##TYPE))) shared_ptr_##TYPE
#define make_shared(TYPE) make_shared_##TYPE

#define define_shared_ptr(TYPE) \
\
struct shared_ptr_##TYPE;    \
void destructor_##TYPE(struct shared_ptr_##TYPE* ptr); \
\
typedef struct shared_ptr_##TYPE \
{ \
    TYPE* (*get)(struct shared_ptr_##TYPE ptr); \
    void (*remove)(struct shared_ptr_##TYPE ptr); \
    void (*reset)(struct shared_ptr_##TYPE ptr, TYPE elem); \
    struct shared_ptr_##TYPE (*clone)(struct shared_ptr_##TYPE ptr); \
    void (*destructor)(struct shared_ptr_##TYPE* ptr); \
\
    struct \
    { \
        TYPE* elem; \
        unsigned* count; \
    } _; \
}  shared_ptr_##TYPE; \
\
TYPE* get_##TYPE(struct shared_ptr_##TYPE ptr) \
{ \
    return ptr._.elem; \
} \
\
void remove_##TYPE(shared_ptr_##TYPE ptr) \
{ \
    if ( * (ptr._.count) <= 1) \
    { \
        free(ptr._.elem); \
        free(ptr._.count); \
    } \
    else \
    { \
        *(ptr._.count) -= 1; \
    } \
    ptr._.elem = NULL; \
    ptr._.count = NULL; \
} \
\
void reset_##TYPE(shared_ptr_##TYPE ptr, TYPE elem) \
{ \
    ptr.remove(ptr); \
    ptr._.elem = malloc(sizeof(TYPE)); \
    *(ptr._.elem) = elem; \
    ptr._.count = malloc(sizeof(unsigned)); \
    *(ptr._.count) = 1; \
} \
\
shared_ptr_##TYPE clone_##TYPE(shared_ptr_##TYPE ptr) \
{ \
    *ptr._.count += 1; \
    return ptr; \
} \
\
void destructor_##TYPE(shared_ptr_##TYPE* ptr) \
{ \
    (*ptr).remove(*ptr); \
    printf("destructor\n"); \
} \
\
shared_ptr_##TYPE  make_shared_##TYPE(TYPE elem) \
{ \
    shared_ptr_##TYPE ptr; \
    \
    ptr.clone = &clone_##TYPE; \
    ptr.get = &get_##TYPE; \
    ptr.reset = &reset_##TYPE; \
    ptr.remove = &remove_##TYPE; \
    ptr.destructor = &destructor_##TYPE; \
    \
    ptr._.elem = malloc(sizeof(TYPE)); \
    *(ptr._.elem) = elem; \
    ptr._.count = malloc(sizeof(unsigned)); \
    *(ptr._.count) = 1; \
    \
    return ptr; \
} \

//typedef shared_ptr_##TYPE __attribute__((cleanup(destructor_##TYPE))) shared_ptr_##TYPE;



#endif // SHARED_PTR_H
