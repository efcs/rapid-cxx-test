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
        int run();
        
    private:
        test_suite m_ts;
    };
}                                                   // namespace rapid_cxx_test
#endif /* RAPID_CXX_TEST_RUNNER_HPP */