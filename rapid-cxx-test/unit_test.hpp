#ifndef RAPID_CXX_TEST_UNIT_TEST_HPP
#define RAPID_CXX_TEST_UNIT_TEST_HPP

# include "common.hpp"
# include "observer.hpp"
# include "runner.hpp"


////////////////////////////////////////////////////////////////////////////////
//                          TEST_SUITE
////////////////////////////////////////////////////////////////////////////////
# define TEST_SUITE(Name)                                           \
namespace Name                                                      \
{                                                                   \
    int unit_test_main(int, char**);                                \
}                                                                   \
int main(int argc, char **argv)                                     \
{                                                                   \
    return Name::unit_test_main(argc, argv);                        \
}                                                                   \
namespace Name                                                      \
{                                                                   \
    inline ::rapid_cxx_test::test_suite & get_test_suite() noexcept \
    {                                                               \
        static ::rapid_cxx_test::test_suite m_suite(#Name);         \
        return m_suite;                                             \
    }
# 

////////////////////////////////////////////////////////////////////////////////
//                         TEST_SUITE_END
////////////////////////////////////////////////////////////////////////////////
# define TEST_SUITE_END()                                       \
    int unit_test_main(int, char**)                             \
    {                                                           \
        ::rapid_cxx_test::test_runner runner(get_test_suite()); \
        return runner.run();                                    \
    }                                                           \
} /* namespace TestSuite */
# 

////////////////////////////////////////////////////////////////////////////////
//                          TEST_CASE
////////////////////////////////////////////////////////////////////////////////

# define TEST_CASE(Name)                                                                                \
    void Name();                                                                                        \
    void RAPID_CXX_TEST_PP_CAT(Name, _invoker)()                                                        \
    {                                                                                                   \
        ::rapid_cxx_test::set_checkpoint(__FILE__,  #Name, __LINE__);                                   \
        Name();                                                                                         \
    }                                                                                                   \
    static ::rapid_cxx_test::registrar                                                                  \
    RAPID_CXX_TEST_PP_CAT(rapid_cxx_test_registrar_, __LINE__)(                                         \
        get_test_suite()                                                                                \
      , ::rapid_cxx_test::test_case{__FILE__, #Name, __LINE__, & RAPID_CXX_TEST_PP_CAT(Name, _invoker)} \
      );                                                                                                \
    void Name()
# 

////////////////////////////////////////////////////////////////////////////////
//                          
////////////////////////////////////////////////////////////////////////////////
# define TEST_WARN(...) 
# define TEST_CHECK(...)
# define TEST_REQUIRE(...)
# define TEST_ASSERT(...)
# define TEST_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)

# define TEST_NO_THROW(...)
# define TEST_THROWS(Except, ...)


#endif /* RAPID_CXX_TEST_UNIT_TEST_HPP */
