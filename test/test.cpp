#include "rapid-cxx-test.hpp"
#include <iostream>
#include <vector>
#include <list>

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
    
    // check collections equal
    std::vector<int> const col1 = { 0, 1, 2, 3 };
    std::list<int> const col2 = { 0, 1, 2, 3 };
    
    TEST_WARN_EQUAL_COLLECTIONS(
        col1.begin(), col1.end()
      , col2.begin(), col2.end()
      );
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        col1.begin(), col1.end()
      , col2.begin(), col2.end()
      );
    
    TEST_REQUIRE_EQUAL_COLLECTIONS(
        col1.begin(), col1.end()
      , col2.begin(), col2.end()
      );
    
    TEST_ASSERT_EQUAL_COLLECTIONS(
        col1.begin(), col1.end()
      , col2.begin(), col2.end()
      );
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

TEST_CASE(collections_equal_warn_test)
{
    std::vector<int> const col1 = { 0, 1, 2, 3 };
    std::list<int> const col2 = { 0, 1 };
    
    TEST_WARN_EQUAL_COLLECTIONS(
        col1.begin(), col1.end()
      , col2.begin(), col2.end()
      );
}

TEST_CASE(collections_check_equal_fail_test)
{
    std::vector<int> const col1 = { 0, 1, 2, 3 };
    std::list<int> const col2 = { 0, 1 };
    
    TEST_CHECK_EQUAL_COLLECTIONS(
        col1.begin(), col1.end()
      , col2.begin(), col2.end()
      );
}

TEST_CASE(collections_require_equal_fail_test)
{
    std::vector<int> const col1 = { 0, 1, 2, 3 };
    std::list<int> const col2 = { 0, 1 };
    
    TEST_REQUIRE_EQUAL_COLLECTIONS(
        col1.begin(), col1.end()
      , col2.begin(), col2.end()
      );
    TEST_ASSERT(false);
}

TEST_SUITE_END()