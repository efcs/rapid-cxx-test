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
# define TEST_SET_CHECKPOINT() ::rapid_cxx_test::set_checkpoint(__FILE__, TEST_FUNC_NAME(), __LINE__)

# define TEST_WARN(...)                                                        \
    do {                                                                       \
        TEST_SET_CHECKPOINT();                                                 \
        ::rapid_cxx_test::test_outcome m_f{                                    \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_WARN(" #__VA_ARGS__ ")", ""                                \
            };                                                                 \
        if (not (__VA_ARGS__)) {                                               \
            m_f.type = ::rapid_cxx_test::failure_type::warn;                   \
        }                                                                      \
        ::rapid_cxx_test::get_observer().report(m_f);                          \
    } while (false)
# 

# define TEST_CHECK(...)                                                       \
    do {                                                                       \
        TEST_SET_CHECKPOINT();                                                 \
        ::rapid_cxx_test::test_outcome m_f{                                    \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_CHECK(" #__VA_ARGS__ ")", ""                               \
            };                                                                 \
        if (not (__VA_ARGS__)) {                                               \
            m_f.type = ::rapid_cxx_test::failure_type::check;                  \
        }                                                                      \
        ::rapid_cxx_test::get_observer().report(m_f);                          \
    } while (false)
#

# define TEST_REQUIRE(...)                                                     \
    do {                                                                       \
        TEST_SET_CHECKPOINT();                                                 \
        ::rapid_cxx_test::test_outcome m_f{                                    \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_REQUIRE(" #__VA_ARGS__ ")", ""                             \
            };                                                                 \
        if (not (__VA_ARGS__)) {                                               \
            m_f.type = ::rapid_cxx_test::failure_type::require;                \
        }                                                                      \
        ::rapid_cxx_test::get_observer().report(m_f);                          \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                \
            return;                                                            \
        }                                                                      \
    } while (false)
# 
    
# define TEST_ASSERT(...)                                                      \
    do {                                                                       \
        TEST_SET_CHECKPOINT();                                                 \
        ::rapid_cxx_test::test_outcome m_f{                                    \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_ASSERT(" #__VA_ARGS__ ")", ""                              \
            };                                                                 \
        if (not (__VA_ARGS__)) {                                               \
            m_f.type = ::rapid_cxx_test::failure_type::assert;                 \
        }                                                                      \
        ::rapid_cxx_test::get_observer().report(m_f);                          \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                \
            std::abort();                                                      \
        }                                                                      \
    } while (false)
# 

# define TEST_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)

# define TEST_WARN_NO_THROW(...)                                                       \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_WARN_NO_THROW(" #__VA_ARGS__ ")", ""                               \
            };                                                                         \
        try {                                                                          \
            (__VA_ARGS__);                                                             \
        } catch (...) {                                                                \
            m_f.type = ::rapid_cxx_test::failure_type::warn;                           \
        }                                                                              \
        ::rapid_cxx_test::get_observer().report(m_f);                                  \
    } while (false)
# 

# define TEST_WARN_THROWS(Expr, ...)                                                   \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_WARN_THROWS(" #Expr, #__VA_ARGS__ ")", ""                          \
            };                                                                         \
        try {                                                                          \
            (__VA_ARGS__);                                                             \
            m_f.type = ::rapid_cxx_test::failure_type::warn;                           \
        } catch (Expr const &) {}                                                      \
        ::rapid_cxx_test::get_observer().report(m_f);                                  \
    } while (false)
# 


# define TEST_CHECK_NO_THROW(...)                                                      \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_CHECK_NO_THROW(" #__VA_ARGS__ ")", ""                              \
            };                                                                         \
        try {                                                                          \
            (__VA_ARGS__);                                                             \
        } catch (...) {                                                                \
            m_f.type = ::rapid_cxx_test::failure_type::check;                          \
        }                                                                              \
        ::rapid_cxx_test::get_observer().report(m_f);                                  \
    } while (false)
#

# define TEST_CHECK_THROWS(Except, ...)                                                \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_CHECK_THROWS(" #Except "," #__VA_ARGS__ ")", ""                    \
            };                                                                         \
        try {                                                                          \
            (__VA_ARGS__);                                                             \
            m_f.type = ::rapid_cxx_test::failure_type::check;                          \
        } catch (Expr const &) {}                                                      \
        ::rapid_cxx_test::get_observer().report(m_f);                                  \
    } while (false)
# 


# define TEST_REQUIRE_NO_THROW(...)                                                    \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_REQUIRE_NO_THROW(" #__VA_ARGS__ ")", ""                            \
            };                                                                         \
        try {                                                                          \
            (__VA_ARGS__);                                                             \
        } catch (...) {                                                                \
            m_f.type = ::rapid_cxx_test::failure_type::require;                        \
        }                                                                              \
        ::rapid_cxx_test::get_observer().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            return;                                                                    \
        }                                                                              \
    } while (false)
#

# define TEST_REQUIRE_THROWS(Except, ...)                                              \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_REQUIRE_THROWS(" #Except "," #__VA_ARGS__ ")", ""                  \
            };                                                                         \
        try {                                                                          \
            (__VA_ARGS__);                                                             \
            m_f.type = ::rapid_cxx_test::failure_type::require;                        \
        } catch (Expr const &) {}                                                      \
        ::rapid_cxx_test::get_observer().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            return;                                                                    \
        }                                                                              \
    } while (false)
# 


# define TEST_ASSERT_NO_THROW(...)                                                     \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_ASSERT_NO_THROW(" #__VA_ARGS__ ")", ""                             \
            };                                                                         \
        try {                                                                          \
            (__VA_ARGS__);                                                             \
        } catch (...) {                                                                \
            m_f.type = ::rapid_cxx_test::failure_type::assert;                         \
        }                                                                              \
        ::rapid_cxx_test::get_observer().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            std::abort();                                                              \
        }                                                                              \
    } while (false)
#


# define TEST_ASSERT_THROWS(Except, ...)                                               \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_ASSERT_THROWS(" #Except "," #__VA_ARGS__ ")", ""                   \
            };                                                                         \
        try {                                                                          \
            (__VA_ARGS__);                                                             \
            m_f.type = ::rapid_cxx_test::failure_type::assert;                         \
        } catch (Expr const &) {}                                                      \
        ::rapid_cxx_test::get_observer().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            std::abort();                                                              \
        }                                                                              \
    } while (false)
#


#endif /* RAPID_CXX_TEST_UNIT_TEST_HPP */
