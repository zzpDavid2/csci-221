flags = -Wall -Werror -Wextra -pedantic -std=c++17 -g
CXX = clang++

test: test_bin
	./test_bin

test_bin: test.cpp sorted_lists.cpp cars.cpp sorted_lists.hpp cars.hpp
	$(CXX) $(flags) -o $@ test.cpp sorted_lists.cpp cars.cpp

clean:
	rm -f test_bin
