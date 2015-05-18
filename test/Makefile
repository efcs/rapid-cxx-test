
.PHONY: all
all:
	$(CXX) -std=c++11 -Wall -Wextra -pedantic -I.. test.cpp -o cxx11.out
	$(CXX) -std=c++03 -Wall -Wextra -pedantic -Wno-variadic-macros -I.. test.cpp -o cxx03.out
	
.PHONY: clean
clean:
	rm -f cxx11.out cxx03.out