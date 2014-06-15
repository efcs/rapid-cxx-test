#ifndef RAPID_CXX_TEST_UNIT_TEST_HPP
#define RAPID_CXX_TEST_UNIT_TEST_HPP

// the namespace
namespace rapid_cxx_test {
	struct test_result {
		char *name;
		char *message;
	}
}

# define TEST_SUITE(Name)
# define TEST_SUITE_END()

# define TEST_CASE(Name)

# define TEST_WARN(...)
# define TEST_CHECK(...)
# define TEST_REQUIRE(...)
# define TEST_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)

# define TEST_NO_THROW(...)
# define TEST_THROWS(Except, ...)

# define AT_RTIME_EQ(x, y) \
	do {\
		if (x != y) {exit(1);}\
	} while (0)

#endif /* RAPID_CXX_TEST_UNIT_TEST_HPP */
