#include "IContainer.h"
#include "malloc.h"


typedef struct ForwardListData
{
    struct ForwardListData *next;
    data_t data;
} ForwardListData;

void deleteForwardListData(ForwardListData** data)
{
    if (data) return;
    if ((*data)->next)
        deleteForwardListData(&(*data)->next);
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
        ForwardListData* begin;
    } _;
} ForwardList;

data_t pop_ForwardList(IContainer* container)
{
    if (container && ! container->empty(container) )
    {
        ForwardList* list = (ForwardList*)container;
        ForwardListData* data = list->_.begin;
        data_t elem = data->data;
        list->_.begin = list->_.begin->next;
        data->next = NULL;
        deleteForwardListData(&data);
        return elem;
    }
    return -1;
}

void pushBack_ForwardList(IContainer* container, data_t element)
{
    if(container)
    {
        ForwardList* list = (ForwardList*)container;
        ForwardListData* data = list->_.begin;
        if (! data)
        {
            list->_.begin = malloc(sizeof(ForwardListData));
            list->_.begin->data = element;
            list->_.begin->next = NULL;
        }
        else
        {
            while (data->next)
                data = data->next;
            data->next = malloc(sizeof(ForwardListData));
            data->next->data = element;
            data->next->next = NULL;
        }
    }
}

unsigned size_ForwardList(IContainer* container)
{
    int size = 0;
    if(container)
    {
        ForwardList* list = (ForwardList*)container;
        ForwardListData* data = list->_.begin;
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

bool empty_ForwardList(IContainer* container)
{
    return container->size(container) == 0;
}

data_t get_ForwardList(IContainer* container, unsigned index)
{
    if(container)
    {
        ForwardList* list = (ForwardList*)container;
        ForwardListData* data = list->_.begin;
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

void merge_ForwardList(IContainer* c1, IContainer* c2)
{
    while( ! c2->empty(c2))
    {
        int value = c2->pop(c2);
        c1->push_back(c1, value);
    }
}


void destructor_ForwardList(IContainer** container)
{
    if(container)
    {
        ForwardList* list = (ForwardList*)*container;
        deleteForwardListData(&list->_.begin);
        free(list);
        *container = NULL;
    }
}



IContainer* newForwardList()
{
    ForwardList* list = malloc(sizeof(ForwardList));

    list->pop = &pop_ForwardList;
    list->push_back = &pushBack_ForwardList;
    list->size = &size_ForwardList;
    list->empty = &empty_ForwardList;
    list->get = &get_ForwardList;
    list->destructor = &destructor_ForwardList;
    list->merge = &merge_ForwardList;

    list->_.begin = NULL;

    return (IContainer*)list;
}
