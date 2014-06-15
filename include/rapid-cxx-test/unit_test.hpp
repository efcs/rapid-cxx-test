#ifndef RAPID_CXX_TEST_UNIT_TEST_HPP
#define RAPID_CXX_TEST_UNIT_TEST_HPP

// the namespace
namespace rabid_cxx_test { }

# define TEST_SUITE(Name)
# define TEST_SUITE_END()

# define TEST_CASE(Name)

# define TEST_WARN(...)
# define TEST_CHECK(...)
# define TEST_REQUIRE(...)
# define TEST_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)

# define TEST_NO_THROW(...)
# define TEST_THROWS(Except, ...)

#endif /* RAPID_CXX_TEST_UNIT_TEST_HPP */