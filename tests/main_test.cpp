#include "../testing_framework/cpputest-3.8/include/CppUTest/CommandLineTestRunner.h"

extern "C" {
#include "example.h"
}

TEST_GROUP(MainTestGroup)
{
};

TEST(MainTestGroup, AdditionTest)
{
    int result = addition(2, 3);
    CHECK_EQUAL(5, result);
}

IMPORT_TEST_GROUP(MainTestGroup);