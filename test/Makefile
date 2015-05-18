
ARGS = -Wall -Wextra -pedantic -I.. -DRAPID_CXX_TEST_NO_SYSTEM_HEADER

.PHONY: all
all:
	$(CXX) $(ARGS) -std=c++11 test.cpp -o cxx11.out
	$(CXX) $(ARGS) -std=c++03 -Wno-variadic-macros test.cpp -o cxx03.out
	
.PHONY: clean
clean:
	rm -f cxx11.out cxx03.out