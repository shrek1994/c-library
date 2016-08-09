#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define RUN_TEST(testFunction) \
    printf("%s", #testFunction); \
    fflush(stdout); \
    testFunction ; \
    printf("\r%s \t OK\n", #testFunction)

#define EXPECT_EQ(expected, result) \
    if (expected != result) \
        fprintf(stderr, "\n%s.%s:\nline %d: %s (%d) != %s (%d)\n", \
                __FILE__, __FUNCTION__, __LINE__, #expected, expected, #result, result)

#define EXPECT_TRUE(condition) \
    EXPECT_EQ(true, condition)

#define EXPECT_FALSE(condition) \
    EXPECT_EQ(false, condition)

#define ASSERT_EQ(expected, result) \
    if (expected != result) \
    { \
        fprintf(stderr, "\n%s.%s:\nline %d: %s (%d) != %s (%d)\nTEST INTERRUPT!\n", \
                __FILE__, __FUNCTION__, __LINE__, #expected, expected, #result, result); \
        return; \
    }

#define ASSERT_TRUE(condition) \
    ASSERT_EQ(true, condition)

#define ASSERT_FALSE(condition) \
    ASSERT_EQ(false, condition)

#endif // TEST_H
