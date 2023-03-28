#include "/Users/oanttoor/.brew/Cellar/cpputest/4.0/include/CppUTest/TestHarness.h"

extern "C" {
#include "example.h"
}

TEST_GROUP(ExampleTestGroup)
{
};

TEST(ExampleTestGroup, AdditionTest)
{
    int result = addition(2, 3);
    CHECK_EQUAL(5, result);
}

TEST(ExampleTestGroup, TakeTest)
{
    int result = take_a_from_b(2, 3);
    CHECK_EQUAL(1, result);
}

TEST(ExampleTestGroup, TimesTest)
{
    int result = a_times_b(2, 3);
    CHECK_EQUAL(6, result);
}

IMPORT_TEST_GROUP(ExampleTestGroup);