#include <stdio.h>
#include "shared_ptr.h"

define_shared_ptr(int)

#include <stdio.h>
#include <stdlib.h>
#include "IContainer.h"
#include "ContainerTest.h"

void runUnitTests()
{
    ContainerTest* test = newContainerTest();

    test->runTests(newQueue);
    test->runTests(newForwardList);
    test->runTests(newList);

    test->destructor(&test);

    printf("\nEXIT SUCCESS\n");
    exit(EXIT_SUCCESS);
}

void addFive(shared_ptr_int number)
{
    *(number.get(number)) += 5;
}

int main(int argc, char *argv[])
{
//    runUnitTests();

    shared_ptr(int) number = make_shared(int)(15);
    printf("%d\n", *number.get(number));
    addFive(number.clone(number));
    printf("%d\n", *number.get(number));

    return 0;
}
