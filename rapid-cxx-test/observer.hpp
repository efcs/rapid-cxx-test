#ifndef RAPID_CXX_TEST_OBSERVER_HPP
#define RAPID_CXX_TEST_OBSERVER_HPP

# include "common.hpp"
# include <cstddef>
# include <cstdio>

namespace rapid_cxx_test
{
    class test_observer
    {
    public:
        test_observer() {}
        
        void test_case_begin()
        {
            ++m_testcases;
            clear_failure();
        }
        
        void test_case_end()
        {
            if (m_failure.type != failure_type::none) {
                ++m_testcase_failures;
            }
        }
        
        void report(test_outcome o) noexcept
        {
            ++m_assertions;
            if (o.type == failure_type::none) {
                return;
            }
            else if (o.type == failure_type::warn) {
                ++m_warning_failures;
                report_error(o);
            }
            else if (o.type == failure_type::check) {
                ++m_check_failures;
                report_error(o);
                m_failure = o;
            }
            else if (o.type ==  failure_type::require) {
                ++m_require_failures;
                report_error(o);
                m_failure = o;
            }
            else if (o.type == failure_type::assert) {
                report_error(o);
                m_failure = o;
            }
            else if (o.type == failure_type::uncaught_exception) {
                std::fprintf(stderr
                  , "TEST CASE FAILED WITH UNCAUGHT EXCEPTION:\n    last checkpoint near %s:%u %s\n\n"
                  , o.file, (int)o.line, o.func
                  );
                m_failure = o;
            }
        }
        
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
        
        void print_summary() const noexcept
        {
            auto out = failure_count() ? stderr : stdout;
            std::fprintf(out, "Test Summary:\n");
            std::fprintf(out, "    %lu out of %lu test cases passed.\n", m_testcase_failures, m_testcases);
            std::fprintf(out, "    %lu out of %lu assertions passed.\n", m_assertions - (m_warning_failures + m_check_failures + m_require_failures), m_assertions);
        }
        
    private:
        void report_error(test_outcome o) const noexcept
        {
            std::fprintf(stderr, "In %s:%u %s:\n    Assertion %s failed. %s\n\n"
                , o.file, (unsigned)o.line, o.func, o.expression, o.message ? o.message : ""
              );
        }
        
    private:
        std::size_t m_testcases;
        std::size_t m_testcase_failures;
        std::size_t m_assertions{};
        std::size_t m_warning_failures{};
        std::size_t m_check_failures{};
        std::size_t m_require_failures{};
    
        test_outcome m_failure{failure_type::none, "", "", 0, "", ""};
    };
    
    inline test_observer & get_observer() noexcept
    {
        static test_observer o;
        return o;
    }
}                                                   // namespace rapid_cxx_test
#endif /* RAPID_CXX_TEST_OBSERVER_HPP */