#include "rapid-cxx-test/unit_test.hpp"
#include <iostream>

TEST_SUITE(MySuite)

TEST_CASE(MyTest)
{
    TEST_WARN(true);
    TEST_CHECK(true);
    TEST_REQUIRE(true);
    TEST_ASSERT(true);
    
    TEST_WARN_NO_THROW(false);
    TEST_CHECK_NO_THROW(false);
    TEST_REQUIRE_NO_THROW(false);
    TEST_ASSERT_NO_THROW(false);
}

TEST_CASE(MyTest1)
{
    TEST_WARN(false);
}

TEST_CASE(MyTest2)
{
    TEST_CHECK(false);
}

TEST_CASE(MyTest3)
{
    TEST_REQUIRE(false);
    TEST_ASSERT(false);
}

TEST_CASE(MyTest4)
{
    throw 0;
}

TEST_SUITE_END()