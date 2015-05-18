#ifndef RAPID_CXX_TEST_HPP
#define RAPID_CXX_TEST_HPP

# include <cstddef>
# include <cstdlib>
# include <cstdio>
# include <cassert>

# define RAPID_CXX_TEST_PP_CAT(x, y) RAPID_CXX_TEST_PP_CAT_2(x, y)
# define RAPID_CXX_TEST_PP_CAT_2(x, y) x##y

# define RAPID_CXX_TEST_PP_STR(...) RAPID_CXX_TEST_PP_STR_2(__VA_ARGS__)
# define RAPID_CXX_TEST_PP_STR_2(...) #__VA_ARGS__ 

# if defined(__GNUC__)
#   define TEST_FUNC_NAME() __PRETTY_FUNCTION__
# else
#   define TEST_FUNC_NAME() __func__
# endif

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
{ /* namespace closed in TEST_SUITE_END */                          \
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
} /* namespace opened in TEST_SUITE(...) */
# 

////////////////////////////////////////////////////////////////////////////////
//                          TEST_CASE
////////////////////////////////////////////////////////////////////////////////

# if !defined(__clang__)
#   
# define TEST_CASE(Name)                                                                                \
    void Name();                                                                                        \
    static void RAPID_CXX_TEST_PP_CAT(Name, _invoker)()                                                 \
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
# else /* __clang__ */
#   
# define TEST_CASE(Name)                                                                                \
    void Name();                                                                                        \
    static void RAPID_CXX_TEST_PP_CAT(Name, _invoker)()                                                 \
    {                                                                                                   \
        Name();                                                                                         \
    }                                                                                                   \
    _Pragma("clang diagnostic push")                                                                    \
    _Pragma("clang diagnostic ignored \"-Wglobal-constructors\"")                                       \
    static ::rapid_cxx_test::registrar                                                                  \
    RAPID_CXX_TEST_PP_CAT(rapid_cxx_test_registrar_, __LINE__)(                                         \
        get_test_suite()                                                                                \
      , ::rapid_cxx_test::test_case{__FILE__, #Name, __LINE__, & RAPID_CXX_TEST_PP_CAT(Name, _invoker)} \
      );                                                                                                \
    _Pragma("clang diagnostic pop")                                                                     \
    void Name()
#
# endif /* !defined(__clang__) */


# define TEST_SET_CHECKPOINT() ::rapid_cxx_test::set_checkpoint(__FILE__, TEST_FUNC_NAME(), __LINE__)

////////////////////////////////////////////////////////////////////////////////
//                              TEST_UNSUPPORTED
////////////////////////////////////////////////////////////////////////////////
# define TEST_UNSUPPORTED()                                                                 \
    do {                                                                                    \
        TEST_SET_CHECKPOINT();                                                              \
        ::rapid_cxx_test::test_outcome m_f{                                                 \
          ::rapid_cxx_test::failure_type::unsupported, __FILE__, TEST_FUNC_NAME(), __LINE__ \
          , "", ""                                                                          \
        };                                                                                  \
        ::rapid_cxx_test::get_reporter().report(m_f);                                       \
        return;                                                                             \
    } while (false)
# 


////////////////////////////////////////////////////////////////////////////////
//                            BASIC ASSERTIONS
////////////////////////////////////////////////////////////////////////////////
# define TEST_WARN(...)                                                                \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_WARN(" #__VA_ARGS__ ")", ""                                        \
            };                                                                         \
        if (not (__VA_ARGS__)) {                                                       \
            m_f.type = ::rapid_cxx_test::failure_type::warn;                           \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
    } while (false)
# 

# define TEST_CHECK(...)                                                               \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_CHECK(" #__VA_ARGS__ ")", ""                                       \
            };                                                                         \
        if (not (__VA_ARGS__)) {                                                       \
            m_f.type = ::rapid_cxx_test::failure_type::check;                          \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
    } while (false)
#

# define TEST_REQUIRE(...)                                                             \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_REQUIRE(" #__VA_ARGS__ ")", ""                                     \
            };                                                                         \
        if (not (__VA_ARGS__)) {                                                       \
            m_f.type = ::rapid_cxx_test::failure_type::require;                        \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            return;                                                                    \
        }                                                                              \
    } while (false)
# 
    
# define TEST_ASSERT(...)                                                              \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_ASSERT(" #__VA_ARGS__ ")", ""                                      \
            };                                                                         \
        if (not (__VA_ARGS__)) {                                                       \
            m_f.type = ::rapid_cxx_test::failure_type::assert;                         \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            std::abort();                                                              \
        }                                                                              \
    } while (false)
# 

////////////////////////////////////////////////////////////////////////////////
//                    TEST_WARN_NO_THROW / TEST_WARN_THROW
////////////////////////////////////////////////////////////////////////////////
# define TEST_WARN_NO_THROW(...)                                                       \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_WARN_NO_THROW(" #__VA_ARGS__ ")", ""                               \
            };                                                                         \
        try {                                                                          \
            (static_cast<void>(__VA_ARGS__));                                          \
        } catch (...) {                                                                \
            m_f.type = ::rapid_cxx_test::failure_type::warn;                           \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
    } while (false)
# 

# define TEST_WARN_THROW(Except, ...)                                                  \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_WARN_THROW(" #Except "," #__VA_ARGS__ ")", ""                      \
            };                                                                         \
        try {                                                                          \
            (static_cast<void>(__VA_ARGS__));                                          \
            m_f.type = ::rapid_cxx_test::failure_type::warn;                           \
        } catch (Except const &) {}                                                    \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
    } while (false)
# 

////////////////////////////////////////////////////////////////////////////////
//                    TEST_CHECK_NO_THROW / TEST_CHECK_THROW
////////////////////////////////////////////////////////////////////////////////
# define TEST_CHECK_NO_THROW(...)                                                      \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_CHECK_NO_THROW(" #__VA_ARGS__ ")", ""                              \
            };                                                                         \
        try {                                                                          \
            (static_cast<void>(__VA_ARGS__));                                          \
        } catch (...) {                                                                \
            m_f.type = ::rapid_cxx_test::failure_type::check;                          \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
    } while (false)
#

# define TEST_CHECK_THROW(Except, ...)                                                 \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_CHECK_THROW(" #Except "," #__VA_ARGS__ ")", ""                     \
            };                                                                         \
        try {                                                                          \
            (static_cast<void>(__VA_ARGS__));                                          \
            m_f.type = ::rapid_cxx_test::failure_type::check;                          \
        } catch (Except const &) {}                                                    \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
    } while (false)
# 


////////////////////////////////////////////////////////////////////////////////
//                    TEST_REQUIRE_NO_THROW / TEST_REQUIRE_THROWs
////////////////////////////////////////////////////////////////////////////////
# define TEST_REQUIRE_NO_THROW(...)                                                    \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_REQUIRE_NO_THROW(" #__VA_ARGS__ ")", ""                            \
            };                                                                         \
        try {                                                                          \
            (static_cast<void>(__VA_ARGS__));                                          \
        } catch (...) {                                                                \
            m_f.type = ::rapid_cxx_test::failure_type::require;                        \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            return;                                                                    \
        }                                                                              \
    } while (false)
#

# define TEST_REQUIRE_THROW(Except, ...)                                               \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_REQUIRE_THROW(" #Except "," #__VA_ARGS__ ")", ""                   \
            };                                                                         \
        try {                                                                          \
            (static_cast<void>(__VA_ARGS__));                                          \
            m_f.type = ::rapid_cxx_test::failure_type::require;                        \
        } catch (Except const &) {}                                                    \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            return;                                                                    \
        }                                                                              \
    } while (false)
# 

////////////////////////////////////////////////////////////////////////////////
//                    TEST_ASSERT_NO_THROW / TEST_ASSERT_THROW
////////////////////////////////////////////////////////////////////////////////
# define TEST_ASSERT_NO_THROW(...)                                                     \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_ASSERT_NO_THROW(" #__VA_ARGS__ ")", ""                             \
            };                                                                         \
        try {                                                                          \
            (static_cast<void>(__VA_ARGS__));                                          \
        } catch (...) {                                                                \
            m_f.type = ::rapid_cxx_test::failure_type::assert;                         \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            std::abort();                                                              \
        }                                                                              \
    } while (false)
#


# define TEST_ASSERT_THROW(Except, ...)                                                \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
            ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__ \
            , "TEST_ASSERT_THROW(" #Except "," #__VA_ARGS__ ")", ""                    \
            };                                                                         \
        try {                                                                          \
            (static_cast<void>(__VA_ARGS__));                                          \
            m_f.type = ::rapid_cxx_test::failure_type::assert;                         \
        } catch (Except const &) {}                                                    \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            std::abort();                                                              \
        }                                                                              \
    } while (false)
#

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

# define TEST_WARN_EQUAL_COLLECTIONS(...)                                              \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
          ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__   \
          , "TEST_WARN_EQUAL_COLLECTIONS(" #__VA_ARGS__ ")", ""                        \
        };                                                                             \
        if (not ::rapid_cxx_test::detail::check_equal_collections_impl(__VA_ARGS__)) { \
            m_f.type = ::rapid_cxx_test::failure_type::warn;                           \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
    } while (false)
# 

# define TEST_CHECK_EQUAL_COLLECTIONS(...)                                             \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
          ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__   \
          , "TEST_CHECK_EQUAL_COLLECTIONS(" #__VA_ARGS__ ")", ""                       \
        };                                                                             \
        if (not ::rapid_cxx_test::detail::check_equal_collections_impl(__VA_ARGS__)) { \
            m_f.type = ::rapid_cxx_test::failure_type::check;                          \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
    } while (false)
# 

# define TEST_REQUIRE_EQUAL_COLLECTIONS(...)                                           \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
          ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__   \
          , "TEST_REQUIRE_EQUAL_COLLECTIONS(" #__VA_ARGS__ ")", ""                     \
        };                                                                             \
        if (not ::rapid_cxx_test::detail::check_equal_collections_impl(__VA_ARGS__)) { \
            m_f.type = ::rapid_cxx_test::failure_type::require;                        \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
            return;                                                                    \
        }                                                                              \
    } while (false)
# 

# define TEST_ASSERT_EQUAL_COLLECTIONS(...)                                            \
    do {                                                                               \
        TEST_SET_CHECKPOINT();                                                         \
        ::rapid_cxx_test::test_outcome m_f{                                            \
          ::rapid_cxx_test::failure_type::none, __FILE__, TEST_FUNC_NAME(), __LINE__   \
          , "TEST_ASSERT_EQUAL_COLLECTIONS(" #__VA_ARGS__ ")", ""                      \
        };                                                                             \
        if (not ::rapid_cxx_test::detail::check_equal_collections_impl(__VA_ARGS__)) { \
            m_f.type = ::rapid_cxx_test::failure_type::assert;                         \
        }                                                                              \
        ::rapid_cxx_test::get_reporter().report(m_f);                                  \
        if (m_f.type != ::rapid_cxx_test::failure_type::none) {                        \
          ::std::abort();                                                              \
        }                                                                              \
    } while (false)
#
    
////////////////////////////////////////////////////////////////////////////////
//                            TEST_STATIC_ASSERT
////////////////////////////////////////////////////////////////////////////////
# define TEST_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////
//                      TEST_SAME_TYPE/TEST_NOT_SAME_TYPE
////////////////////////////////////////////////////////////////////////////////
# define TEST_SAME_TYPE(...) \
    static_assert(::rapid_cxx_test::detail::is_same<__VA_ARGS__>::value, "is_same<" #__VA_ARGS__ ">::value")
# 

# define TEST_NOT_SAME_TYPE(...) \
    static_assert(not ::rapid_cxx_test::detail::is_same<__VA_ARGS__>::value, "not is_same<" #__VA_ARGS__ ">::value")

namespace rapid_cxx_test
{
    constexpr std::size_t test_case_max = 256;
    
    using invoker_t = void(*)();
    
    ////////////////////////////////////////////////////////////////////////////
    struct test_case
    {
        const char *file;
        const char *func;
        std::size_t line;
        invoker_t invoke;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    enum class failure_type
    {
        none, 
        unsupported, 
        warn,
        check, 
        require, 
        assert, 
        uncaught_exception
    };
    
    ////////////////////////////////////////////////////////////////////////////
    struct test_outcome
    {
        failure_type type;
        const char *file;
        const char *func;
        std::size_t line;
        const char *expression;
        const char *message;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    struct checkpoint
    {
        const char *file;
        const char *func;
        std::size_t line;
    };
    
    namespace detail
    {
        inline checkpoint & global_checkpoint() noexcept
        {
            static checkpoint cp{"", "", 0};
            return cp;
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline void set_checkpoint(const char* file, const char* func, std::size_t line) noexcept
    {
        auto & cp = detail::global_checkpoint();
        cp.file = file;
        cp.func = func;
        cp.line = line;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline checkpoint const & get_checkpoint() noexcept
    {
        return detail::global_checkpoint();
    }
    
    ////////////////////////////////////////////////////////////////////////////
    class test_suite
    {
    public:
        test_suite(const char *xname) noexcept
          : m_name(xname), m_tests(), m_size(0)
        {
            assert(xname);
        }
        
        test_suite(test_suite const &) = delete;
        test_suite & operator=(test_suite const &) = delete;
    
    public:
        const char *name() const noexcept { return m_name; } 
        
        std::size_t size() const noexcept { return m_size; }
        
        test_case const & operator[](std::size_t i) const noexcept
        {
            assert(i < m_size);
            return m_tests[i];
        }
        
        test_case const * begin() const noexcept
        {
            return m_tests;
        }
        
        test_case const * end() const noexcept
        {
            return m_tests + m_size;
        }

    public:
        std::size_t register_test(test_case tc) noexcept
        {
            assert(m_size < test_case_max);
            m_tests[m_size] = tc;
            return m_size++;
        }
        
    private:
        const char* m_name;
        // Since fast compile times in a priority, we use simple containers
        // with hard limits.
        test_case m_tests[test_case_max];
        std::size_t m_size;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    class registrar
    {
    public:
        registrar(test_suite & st, test_case tc) noexcept
        {
            st.register_test(tc);
        }
    };
    
    ////////////////////////////////////////////////////////////////////////////
    class test_reporter
    {
    public:
        test_reporter() {}
        
        test_reporter(test_reporter const &) = delete;
        test_reporter const & operator=(test_reporter const &) = delete; 
        
        void test_case_begin()
        {
            ++m_testcases;
            clear_failure();
        }
        
        void test_case_end()
        {
            if (m_failure.type != failure_type::none 
                && m_failure.type !=  failure_type::unsupported) {
                ++m_testcase_failures;
            }
        }
        
# if defined(__GNUC__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wswitch-default"
# endif
        // Each assertion and failure is reported through this function.
        void report(test_outcome o) noexcept
        {
            ++m_assertions;
            switch (o.type)
            {
            case failure_type::none:
                break;
            case failure_type::unsupported:
                ++m_unsupported;
                m_failure = o;
                break;
            case failure_type::warn:
                ++m_warning_failures;
                report_error(o);
                break;
            case failure_type::check:
                ++m_check_failures;
                report_error(o);
                m_failure = o;
                break;
            case failure_type::require:
                ++m_require_failures;
                report_error(o);
                m_failure = o;
                break;
            case failure_type::assert:
                report_error(o);
                break;
            case failure_type::uncaught_exception:
                std::fprintf(stderr
                    , "Test case FAILED with uncaught exception:\n"
                      "    last checkpoint near %s::%lu %s\n\n"
                    , o.file, o.line, o.func
                    );
                m_failure = o;
                break;
            }
        }
# if defined(__GNUC__)
#   pragma GCC diagnostic pop
# endif
        
        test_outcome current_failure() const noexcept
        {
            return m_failure;
        }
        
        void clear_failure() 
        {
            m_failure.type = failure_type::none;
            m_failure.file = "";
            m_failure.func = "";
            m_failure.line = 0;
            m_failure.expression = "";
            m_failure.message = "";
        }
        
        std::size_t test_case_count() const noexcept
        {
            return m_testcases;
        }
        
        std::size_t test_case_failure_count() const noexcept
        {
            return m_testcase_failures;
        }
        
        std::size_t unsupported_count() const noexcept
        { return m_unsupported; }
        
        std::size_t assertion_count() const noexcept
        { return m_assertions; }
        
        std::size_t warning_failure_count() const noexcept
        { return m_warning_failures; }
        
        std::size_t check_failure_count() const noexcept
        { return m_check_failures; }
        
        std::size_t require_failure_count() const noexcept
        { return m_require_failures; }
        
        std::size_t failure_count() const noexcept
        { return m_check_failures + m_require_failures; }
        
        
        // Print a summary of what was run and the outcome.
        void print_summary(const char* suitename) const noexcept
        {
            auto out = failure_count() ? stderr : stdout;
            auto testcases_run = m_testcases - m_unsupported;
            std::fprintf(out, "Summary for testsuite %s:\n", suitename);
            std::fprintf(out, "    %lu of %lu test cases passed.\n", testcases_run - m_testcase_failures, testcases_run);
            std::fprintf(out, "    %lu of %lu assertions passed.\n", m_assertions - (m_warning_failures + m_check_failures + m_require_failures), m_assertions);
            std::fprintf(out, "    %lu unsupported test case%s.\n", m_unsupported, (m_unsupported != 1 ? "s" : ""));
        }
        
    private:
        void report_error(test_outcome o) const noexcept
        {
            std::fprintf(stderr, "%s:%lu Assertion %s failed.\n    in function: %s\n    %s\n"
                , o.file, o.line, o.expression, o.func,  o.message ? o.message : ""
              );
        }
        
    private:
        // counts of testcases, failed testcases, and unsupported testcases.
        std::size_t m_testcases{};
        std::size_t m_testcase_failures{};
        std::size_t m_unsupported{};
        
        // counts of assertions and assertion failures.
        std::size_t m_assertions{};
        std::size_t m_warning_failures{};
        std::size_t m_check_failures{};
        std::size_t m_require_failures{};
    
        // The last failure. This is cleared between testcases.
        test_outcome m_failure{failure_type::none, "", "", 0, "", ""};
    };
    
    ////////////////////////////////////////////////////////////////////////////
    inline test_reporter & get_reporter() noexcept
    {
        static test_reporter o;
        return o;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    class test_runner
    {
    public:
        test_runner(test_suite & ts)
          : m_ts(ts)
        {}
        
        test_runner(test_runner const &) = delete;
        test_runner operator=(test_runner const &) = delete;
        
    public:
        int run()
        {
            // for each testcase
            for (auto & tc : m_ts) {
                set_checkpoint(tc.file, tc.func, tc.line);
                get_reporter().test_case_begin();
                try {
                    tc.invoke();
                } catch (...) {
                    test_outcome o;
                    o.type = failure_type::uncaught_exception;
                    o.file = get_checkpoint().file;
                    o.func = get_checkpoint().func;
                    o.line = get_checkpoint().line;
                    o.expression = "";
                    o.message = "";
                    get_reporter().report(o);
                }
                get_reporter().test_case_end();
            }
            get_reporter().print_summary(m_ts.name());
            // return 0 if no failures, 1 otherwise.
            return get_reporter().failure_count()  ? EXIT_FAILURE : EXIT_SUCCESS;
        }
        
    private:
        test_suite & m_ts;
    };
    
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        template <class T, class U>
        struct is_same
        {
            enum { value = 0 };
        };
        
        template <class T>
        struct is_same<T, T>
        {
            enum { value = 1 };
        };
        
        template <class Iter1, class Iter2>
        bool check_equal_collections_impl(
            Iter1 start1, Iter1 const end1
          , Iter2 start2, Iter2 const end2
          )
        {
            while (start1 != end1 && start2 != end2) {
                if (*start1 != *start2) {
                    return false;
                }
                ++start1; ++start2;
            }
            return (start1 == end1 && start2 == end2);
        }
    }                                                       // namespace detail
    
}                                                    // namespace rapid_cxx_test

#endif /* RAPID_CXX_TEST_HPP */
