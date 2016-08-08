#include "IContainer.h"
#include "malloc.h"

typedef struct QueueData
{
    struct QueueData *next;
    data_t data;
} QueueData;

void deleteQueueData(QueueData** data)
{
    if (data) return;
    if ((*data)->next)
        deleteQueueData(&(*data)->next);
    free(*data);
    *data = NULL;
}

typedef struct
{
    data_t (*pop)(struct IContainer*);
    void (*push_back)(struct IContainer*, data_t element);
    unsigned (*size)(struct IContainer*);
    bool (*empty)(struct IContainer*);
    data_t (*get)(struct IContainer*, unsigned index);
    void (*destructor)(struct IContainer**);

    void (*merge)(struct IContainer*, struct IContainer*);

    struct
    {
        QueueData* head;
    } _;
} Queue;

data_t pop_Queue(IContainer* container)
{
    if (container && ! container->empty(container) )
    {
        Queue* queue = (Queue*)container;
        QueueData* data = queue->_.head;
        data_t elem = data->data;
        queue->_.head = queue->_.head->next;
        data->next = NULL;
        deleteQueueData(&data);
        return elem;
    }
    return -1;
}

void pushBack_Queue(IContainer* container, data_t element)
{
    if(container)
    {
        Queue* queue = (Queue*)container;
        QueueData* data = queue->_.head;
        if (! data)
        {
            queue->_.head = malloc(sizeof(QueueData));
            queue->_.head->data = element;
            queue->_.head->next = NULL;
        }
        else
        {
            while (data->next)
                data = data->next;
            data->next = malloc(sizeof(QueueData));
            data->next->data = element;
            data->next->next = NULL;
        }
    }
}

unsigned size_Queue(IContainer* container)
{
    int size = 0;
    if(container)
    {
        Queue* queue = (Queue*)container;
        QueueData* data = queue->_.head;
        if (data)
            ++size;
        else
            return size;
        while (data->next)
        {
            ++size;
            data = data->next;
        }
    }
    return size;
}

bool empty_Queue(IContainer* container)
{
    return container->size(container) == 0;
}

data_t get_Queue(IContainer* container, unsigned index)
{
    if(container)
    {
        Queue* queue = (Queue*)container;
        QueueData* data = queue->_.head;
        for (unsigned i = 0; i < index ; ++i)
        {
            if(data)
                data = data->next;
        }
        if(data)
            return data->data;
    }
    return -1;
}


void destructor_Queue(IContainer** container)
{
    if(container)
    {
        IContainer* cont = *container;
        Queue* queue = (Queue*)(cont);
        if(queue->_.head)
            deleteQueueData(&queue->_.head);
        free(queue);
        *container = NULL;
    }
}

void merge_Queue(IContainer* c1, IContainer* c2)
{
    fprintf(stderr, "\n%s, Not implemented yet!\n", __FUNCTION__);
    printf("%s test", "test");

    // to disable warnings
    c1 = c1;
    c2 = c2;
}


IContainer* newQueue()
{
    Queue* queue = malloc(sizeof(Queue));

    queue->pop = &pop_Queue;
    queue->push_back = &pushBack_Queue;
    queue->size = &size_Queue;
    queue->empty = &empty_Queue;
    queue->get = &get_Queue;
    queue->destructor = &destructor_Queue;
    queue->merge = &merge_Queue;

    queue->_.head = NULL;

    return (IContainer*)queue;
}
