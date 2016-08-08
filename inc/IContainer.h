#ifndef CONTAINER_H
#define CONTAINER_H

#ifndef data_t
#define data_t int
#endif

#include <stdbool.h>

typedef struct IContainer
{
    data_t (*const pop)(struct IContainer*);
    void (*const push_back)(struct IContainer*, data_t element);
    unsigned (*const size)(struct IContainer*);
    bool (*const empty)(struct IContainer*);
    data_t (*const get)(struct IContainer*, unsigned index);
    void (*const destructor)(struct IContainer**);

    void (*const merge)(struct IContainer*, struct IContainer*);
} IContainer;

IContainer* newQueue();
IContainer* newForwardList();
IContainer* newList();

#endif // QUEUE_H
