flags = -Wall -Werror -Wextra -pedantic -g

objects = binary_search_tree.o tests.o io.o

tests: binary_search_tree.o tests.o
	gcc binary_search_tree.o tests.o -o tests $(flags)
	./tests

binary_search_tree.o: binary_search_tree.c binary_search_tree.h
	gcc -c binary_search_tree.c -o binary_search_tree.o $(flags)

tests.o: tests.c binary_search_tree.h
	gcc -c tests.c -o tests.o $(flags)

io.o: io.c
	gcc -c io.c -o io.o $(flags)

clean:
	rm -f tests $(objects)
