#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include "stdbool.h"
/* use only to local variable, to arguments in function use shared_ptr_TYPE
 */
#define shared_ptr(TYPE) __attribute__((cleanup(destructor_##TYPE))) shared_ptr_##TYPE
#define make_shared(TYPE) make_shared_##TYPE

#define import_shared_ptr(TYPE) \
\
typedef struct shared_ptr_##TYPE \
{ \
    TYPE* (*get)(struct shared_ptr_##TYPE ptr); \
    void (*remove)(struct shared_ptr_##TYPE ptr); \
    void (*reset)(struct shared_ptr_##TYPE ptr, TYPE elem); \
    struct shared_ptr_##TYPE (*clone)(struct shared_ptr_##TYPE ptr); \
    void (*destructor)(struct shared_ptr_##TYPE* ptr); \
    bool (*is_initialized)(struct shared_ptr_##TYPE ptr); \
\
    struct \
    { \
        TYPE* elem; \
        unsigned* count; \
    } _; \
}  shared_ptr_##TYPE; \
\
shared_ptr_##TYPE make_shared_##TYPE(TYPE elem); \
void destructor_##TYPE(struct shared_ptr_##TYPE* ptr); \


//typedef shared_ptr_##TYPE __attribute__((cleanup(destructor_##TYPE))) shared_ptr_##TYPE;



#endif // SHARED_PTR_H
