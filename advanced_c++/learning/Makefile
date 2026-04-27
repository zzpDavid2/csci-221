flags = -Wall -Werror -Wextra -pedantic -std=c++17 -g
CXX = clang++

test: inheritance stl templates
	./inheritance
	./stl
	./templates

inheritance: inheritance.cpp inheritance.hpp
	$(CXX) $(flags) -o $@ inheritance.cpp

stl: stl.cpp stl.hpp
	$(CXX) $(flags) -o $@ stl.cpp

templates: templates.cpp templates.hpp
	$(CXX) $(flags) -o $@ templates.cpp

clean:
	rm -f inheritance stl templates
