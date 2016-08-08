#include "IContainer.h"
#include "malloc.h"

typedef struct ListData
{
    struct ListData *next;
    struct ListData *prev;
    data_t data;
} ListData;

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
        ListData* begin;
        ListData* last;
        unsigned size;
    } _;
} List;


void deleteListData(ListData** data)
{
    if (data) return;
    if ((*data)->next->next)
        deleteListData(&(*data)->next);
    free(*data);
    *data = NULL;
}

data_t pop_List(IContainer* container)
{
    if (container && ! container->empty(container) )
    {
        List* list = (List*)container;
        ListData* data = list->_.begin;
        data_t elem = data->data;

        if(list->_.begin == list->_.last)
            list->_.last = NULL;

        list->_.begin = list->_.begin->next;
        data->next = NULL;
        deleteListData(&data);

        --list->_.size;
        return elem;
    }
    return -1;
}

void pushBack_List(IContainer* container, data_t element)
{
    if(container)
    {
        List* list = (List*)container;
        ListData* data = list->_.begin;
        ListData* newElement = malloc(sizeof(ListData));
        newElement->data = element;
        newElement->next = NULL;
        if (! data)
        {
            list->_.begin = newElement;
            list->_.last = newElement;

            newElement->prev = NULL;
        }
        else
        {
            data = list->_.last;

            data->next = newElement;
            list->_.last = newElement;

            newElement->prev = data;
        }
        ++list->_.size;
    }
}

unsigned size_List(IContainer* container)
{
    if(container)
    {
        List* list = (List*)container;
        return list->_.size;
    }
//        ListData* data = list->_.begin;
//        if (data)
//            ++size;
//        else
//            return size;
//        while (data->next)
//        {
//            ++size;
//            data = data->next;
//        }
//    }
    return -1;
}

bool empty_List(IContainer* container)
{
    return container->size(container) == 0;
}

data_t get_List(IContainer* container, unsigned index)
{

    if(container)
    {
        List* list = (List*)container;
        ListData* data;
        if ( index  > list->_.size / 2)
        {
            data = list->_.last;
            for (unsigned i = list->_.size - 1; i > index ; --i)
            {
                if(data)
                    data = data->prev;
            }
        }
        else
        {
            data = list->_.begin;
            for (unsigned i = 0; i < index ; ++i)
            {
                if(data)
                    data = data->next;
            }
        }
        if(data)
            return data->data;
    }
    return -1;
}

void destructor_List(IContainer** container)
{
    if(container)
    {
        List* list = (List*)*container;
        deleteListData(&list->_.begin);
        free(list);
        *container = NULL;
    }
}

void merge_List(IContainer* c1, IContainer* c2)
{
    while( ! c2->empty(c2))
    {
        int value = c2->pop(c2);
        c1->push_back(c1, value);
    }
}

IContainer* newList()
{
    List* list = malloc(sizeof(List));

    list->pop = &pop_List;
    list->push_back = &pushBack_List;
    list->size = &size_List;
    list->empty = &empty_List;
    list->get = &get_List;
    list->destructor = &destructor_List;

    list->merge = &merge_List;

    list->_.begin = NULL;
    list->_.last = NULL;
    list->_.size = 0;

    return (IContainer*)list;
}
