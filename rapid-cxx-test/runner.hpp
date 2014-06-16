#ifndef RAPID_CXX_TEST_RUNNER_HPP
#define RAPID_CXX_TEST_RUNNER_HPP

# include "common.hpp"
# include "observer.hpp"
# include <cstddef>
# include <cstdlib>
# include <cstdio>

namespace rapid_cxx_test
{
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
            for (auto & tc : m_ts) {
                set_checkpoint(tc.file, tc.func, tc.line);
                get_observer().test_case_begin();
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
                    get_observer().report(o);
                }
                get_observer().test_case_end();
            }
            get_observer().print_summary();
            return get_observer().failure_count();
        }
        
    private:
        test_suite & m_ts;
    };
}                                                   // namespace rapid_cxx_test
#endif /* RAPID_CXX_TEST_RUNNER_HPP */