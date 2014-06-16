#include "rapid-cxx-test.hpp"
#include <iostream>

TEST_SUITE(rapid_cxx_test_testsuite)

TEST_CASE(all_pass_test)
{
    TEST_WARN(true);
    TEST_CHECK(true);
    TEST_REQUIRE(true);
    TEST_ASSERT(true);
    
    TEST_WARN_NO_THROW(false);
    TEST_CHECK_NO_THROW(false);
    TEST_REQUIRE_NO_THROW(false);
    TEST_ASSERT_NO_THROW(false);
    
    TEST_WARN_THROW(int, throw 0);
    TEST_CHECK_THROW(int, throw 0);
    TEST_REQUIRE_THROW(int, throw 0);
    TEST_ASSERT_THROW(int, throw 0);
    
    TEST_STATIC_ASSERT(true);
    TEST_SAME_TYPE(int, int);
    TEST_NOT_SAME_TYPE(long, int);
}

TEST_CASE(warn_fail_test)
{
    TEST_WARN(false);
    TEST_WARN_NO_THROW(throw 0);
    TEST_WARN_THROW(int, ((void)0));
}

TEST_CASE(check_fail_test)
{
    TEST_CHECK(false);
    TEST_CHECK_NO_THROW(throw 0);
    TEST_CHECK_THROW(int, ((void)0));
}

TEST_CASE(require_fail_test)
{
    TEST_REQUIRE(false);
}

TEST_CASE(uncaught_exception_test)
{
    throw 0;
}

TEST_CASE(unsupported_two)
{
    TEST_UNSUPPORTED();
}

TEST_SUITE_END()