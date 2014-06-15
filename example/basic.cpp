#include "../include/rapid-cxx-test/unit_test.hpp"

TEST_SUITE(basic_example)

TEST_CASE(compiler_not_useless)
{
    int x = 0;
    AT_RTIME_EQ(x, 0);
    x = 1;
    AT_RTIME_EQ(x, 1);
}

TEST_SUITE_END()
