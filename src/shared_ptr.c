#include <stdlib.h>
#include <stdio.h>
#include "shared_ptr.h"

#define declare_shared_ptr(TYPE) \
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
    ptr._.elem = (TYPE*)malloc(sizeof(TYPE)); \
    *(ptr._.elem) = elem; \
    ptr._.count = (unsigned*)malloc(sizeof(unsigned)); \
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
bool is_initialized_##TYPE(shared_ptr_##TYPE ptr) \
{ \
    return (ptr._.elem != NULL) && *(ptr._.count) > 0;\
} \
\
shared_ptr_##TYPE make_shared_##TYPE(TYPE elem) \
{ \
    shared_ptr_##TYPE ptr; \
    \
    ptr.clone = &clone_##TYPE; \
    ptr.get = &get_##TYPE; \
    ptr.reset = &reset_##TYPE; \
    ptr.remove = &remove_##TYPE; \
    ptr.is_initialized = &is_initialized_##TYPE; \
    ptr.destructor = &destructor_##TYPE; \
    \
    ptr._.elem = (TYPE*)malloc(sizeof(TYPE)); \
    *(ptr._.elem) = elem; \
    ptr._.count = (unsigned*)malloc(sizeof(unsigned)); \
    *(ptr._.count) = 1; \
    \
    return ptr; \
} \

import_shared_ptr(int)
import_shared_ptr(double)
import_shared_ptr(float)
import_shared_ptr(char)
import_shared_ptr(bool)
import_shared_ptr(unsigned)

declare_shared_ptr(int)
declare_shared_ptr(double)
declare_shared_ptr(float)
declare_shared_ptr(char)
declare_shared_ptr(bool)
declare_shared_ptr(unsigned)
