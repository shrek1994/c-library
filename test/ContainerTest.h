#ifndef CONTAINERTEST_H
#define CONTAINERTEST_H

#include "IContainer.h"

typedef struct ContainerTest
{
    void (*runTests)(IContainer* (*constructor)());
    void (*destructor)(struct ContainerTest**);

} ContainerTest;


ContainerTest* newContainerTest();

#endif // CONTAINERTEST_H
