flags = -Wall -Werror -Wextra -pedantic -g
CXX = clang++

test: hello_world
	./hello_world

hello_world: hello_world.cpp
	$(CXX) $(flags) -o $@ $<

clean:
	rm -f hello_world
