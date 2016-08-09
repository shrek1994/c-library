#include <stdlib.h>
#include "SharedPtrTest.h"
#include "shared_ptr.h"
#include "test.h"

import_shared_ptr(int)

int value = 123;

void shouldCreateSharedPtrWithCorrectValue()
{
    shared_ptr(int) sut = make_shared(int) (value);

    EXPECT_EQ(value, *sut.get(sut));
}

void shouldDestroyAfterScope()
{
    shared_ptr_int ptr = make_shared(int) (value);
    {
        shared_ptr(int) weakPtr = ptr;
        *weakPtr.get(weakPtr) += 5;
        EXPECT_EQ(value + 5, *ptr.get(ptr));
    }
    EXPECT_EQ(value + 5, *ptr.get(ptr));
    EXPECT_FALSE(ptr.is_initialized(ptr));
}

void runTests_SharedPtrTest()
{
    printf("\t\tTESTING\n\n");
    RUN_TEST(shouldCreateSharedPtrWithCorrectValue());
//    /RUN_TEST(shouldDestroyAfterScope());
}


void destructor_SharedPtrTest(SharedPtrTest** sharedPtrTest)
{
    printf("destructor_SharedPtrTest\n");
    if (sharedPtrTest && *sharedPtrTest)
    {
        free(*sharedPtrTest);
        *sharedPtrTest = NULL;
    }
}


SharedPtrTest* newSharedPtrTest()
{
    SharedPtrTest* sharedPtrTest = malloc(sizeof(SharedPtrTest));

    sharedPtrTest->runTests = &runTests_SharedPtrTest;
    sharedPtrTest->destructor = &destructor_SharedPtrTest;

    return sharedPtrTest;
}
