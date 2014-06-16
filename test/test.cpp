#include "rapid-cxx-test/unit_test.hpp"
#include <iostream>

TEST_SUITE(MySuite)

TEST_CASE(MyTest1)
{
    std::cout << "IN " << __PRETTY_FUNCTION__ << std::endl;
}

TEST_CASE(MyTest2)
{
    std::cout << "IN " << __PRETTY_FUNCTION__ << std::endl;
}

TEST_CASE(MyTest3)
{
    std::cout << "IN " << __PRETTY_FUNCTION__ << std::endl;
}

TEST_SUITE_END()