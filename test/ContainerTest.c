#include "ContainerTest.h"
#include "malloc.h"
#include "test.h"


void clearContainer(IContainer* container)
{
    // should be empty after test;
    while(! container->empty(container))
        container->pop(container);
    EXPECT_TRUE(container->empty(container));
}

void shouldBeEmptyWhenAddNothing(IContainer* container)
{
    EXPECT_TRUE(container->empty(container));
    EXPECT_EQ(0, container->size(container));
}

void shouldCorrectlyAddAndPopElement(IContainer* container)
{
    ASSERT_TRUE(container->empty(container));

    int value = 123;

    container->push_back(container, value);

    EXPECT_EQ(1, container->size(container));
    EXPECT_FALSE(container->empty(container));

    EXPECT_EQ(value, container->pop(container));
    EXPECT_TRUE(container->empty(container));
}

void shouldCorrectlyReturnSize(IContainer* container)
{
    ASSERT_TRUE(container->empty(container));

    unsigned size = 10, value = 1234;

    for(unsigned i = 0; i < size; ++i)
    {
        container->push_back(container, value);
    }

    EXPECT_FALSE(container->empty(container));
    EXPECT_EQ(size, container->size(container));
}

void shouldCorrectlyReturnValue(IContainer* container)
{
    ASSERT_TRUE(container->empty(container));

    int value = 12;
    unsigned firstIndex = 0;

    container->push_back(container, value);

    EXPECT_EQ(value, container->get(container, firstIndex));
}

void shouldCorrectlyReturnValueInOrder(IContainer* container)
{
    ASSERT_TRUE(container->empty(container));

    int firstValue = 12;
    int secondValue = 34;
    int thirdValue = 56;
    int forthValue = 78;
    int fifthValue = 90;

    container->push_back(container, firstValue);
    container->push_back(container, secondValue);
    container->push_back(container, thirdValue);
    container->push_back(container, forthValue);
    container->push_back(container, fifthValue);

    EXPECT_EQ(firstValue, container->get(container, 0));
    EXPECT_EQ(secondValue, container->get(container, 1));
    EXPECT_EQ(thirdValue, container->get(container, 2));
    EXPECT_EQ(forthValue, container->get(container, 3));
    EXPECT_EQ(fifthValue, container->get(container, 4));
}

void shouldCorrectlyMergeContainers(IContainer* firstContainer, IContainer* secondContainer)
{
    ASSERT_TRUE(firstContainer->empty(firstContainer));
    ASSERT_TRUE(secondContainer->empty(secondContainer));

    int firstValue = 123456789;
    int secondValue = 987654321;
    unsigned sizeAfterMerge = 2;
    unsigned emptySize = 0;

    firstContainer->push_back(firstContainer, firstValue);
    secondContainer->push_back(firstContainer, secondValue);

    firstContainer->merge(firstContainer, secondContainer);

    EXPECT_EQ(sizeAfterMerge, firstContainer->size(firstContainer));
    EXPECT_EQ(emptySize, secondContainer->size(secondContainer));
    EXPECT_EQ(firstValue, firstContainer->get(firstContainer, 0));
    EXPECT_EQ(secondValue, firstContainer->get(firstContainer, 1));
}

void shouldCorrectlyDestructEmptyContainerAndSetNull(IContainer* container)
{
    ASSERT_TRUE(container->empty(container));

    container->destructor(&container);

    EXPECT_FALSE(container);
}

void shouldCorrectlyDestructWithTwoElements(IContainer* container)
{
    container->push_back(container, 10);
    container->push_back(container, 12);

    container->destructor(&container);

    EXPECT_FALSE(container);
}


void runTests_ContainerTest(IContainer* (*constructor)())
{
    printf("\t\tTESTING\n\n");

    IContainer* container = constructor();
    RUN_TEST(shouldCorrectlyDestructEmptyContainerAndSetNull(container));

    container = constructor();
    RUN_TEST(shouldCorrectlyDestructWithTwoElements(container));

    container = constructor();
    RUN_TEST(shouldBeEmptyWhenAddNothing(container));
    clearContainer(container);

    RUN_TEST(shouldCorrectlyAddAndPopElement(container));
    clearContainer(container);

    RUN_TEST(shouldCorrectlyReturnValueInOrder(container));
    clearContainer(container);

    RUN_TEST(shouldCorrectlyReturnSize(container));
    clearContainer(container);

    RUN_TEST(shouldCorrectlyReturnValue(container));
    clearContainer(container);

    IContainer* secondContainer = constructor();
    RUN_TEST(shouldCorrectlyMergeContainers(container, secondContainer));
    secondContainer->destructor(&secondContainer);

    clearContainer(container);
}

void destructor_ContainerTest(ContainerTest** containerTest)
{
    printf("destructor_ContainerTest\n");
    if (containerTest && *containerTest)
    {
        free(*containerTest);
        *containerTest = NULL;
    }
}

ContainerTest* newContainerTest()
{
    ContainerTest* containerTest = malloc(sizeof(ContainerTest));

    containerTest->runTests = &runTests_ContainerTest;
    containerTest->destructor = &destructor_ContainerTest;

    return containerTest;
}
