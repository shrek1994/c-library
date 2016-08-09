#ifndef SHARED_PTRTEST_H
#define SHARED_PTRTEST_H


typedef struct SharedPtrTest
{
    void (*runTests)();
    void (*destructor)(struct SharedPtrTest**);
} SharedPtrTest;

SharedPtrTest* newSharedPtrTest();

#endif // SHARED_PTRTEST_H
