#ifndef RAPID_CXX_TEST_COMMON_HPP
#define RAPID_CXX_TEST_COMMON_HPP

# include <cstddef>
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

namespace rapid_cxx_test
{
    // fwd //
    class test_runner;
    class test_observer;
    
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
        warn,
        check, 
        require, 
        assert, 
        uncaught_exception
    };
    
    inline const char *to_string(failure_type f) noexcept
    {
        switch (f)
        {
            case failure_type::none:
                return "none";
            case failure_type::warn:
                return "TEST_WARN";
            case failure_type::check:
                return "TEST_CHECK";
            case failure_type::require:
                return "TEST_REQUIRE";
            case failure_type::assert:
                return "TEST_ASSERT";
            case failure_type::uncaught_exception:
                return "UNCAUGHT EXCEPTION";
            default:
                assert(!bool("IN DEFAULT CASE"));
                return nullptr;
        }
    }
    
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
    
    inline void set_checkpoint(const char* file, const char* func, std::size_t line) noexcept
    {
        auto & cp = detail::global_checkpoint();
        cp.file = file;
        cp.func = func;
        cp.line = line;
    }
    
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
    
}                                                   // namespace rapid_cxx_test
#endif /* RAPID_CXX_TEST_COMMON_HPP */