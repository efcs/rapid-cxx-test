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
    };
    
    inline test_observer & get_observer() noexcept
    {
        static test_observer o;
        return o;
    }
}                                                   // namespace rapid_cxx_test
#endif /* RAPID_CXX_TEST_OBSERVER_HPP */