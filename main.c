#include <stdio.h>
#include <stdlib.h>

#include "ContainerTest.h"
#include "SharedPtrTest.h"
#include "shared_ptr.h"
import_shared_ptr(int)

void runUnitTests()
{
    ContainerTest* test = newContainerTest();

    test->runTests(newQueue);
    test->runTests(newForwardList);
    test->runTests(newList);

    test->destructor(&test);

    SharedPtrTest* testPtr = newSharedPtrTest();

    testPtr->runTests();
    testPtr->destructor(&testPtr);


    printf("\nEXIT SUCCESS\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    runUnitTests();

    shared_ptr(int) number = make_shared(int)(15);
    printf("%d\n", *number.get(number));
    printf("%d\n", *number.get(number));

    return 0;
}
