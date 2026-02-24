flags = -Wall -Werror -Wextra -pedantic -g

objects = binary_search_tree.o tests.o io.o

run: tests io
	./tests
	./io
	./io -r

tests: binary_search_tree.o tests.o
	gcc binary_search_tree.o tests.o -o tests $(flags)

binary_search_tree.o: binary_search_tree.c binary_search_tree.h
	gcc -c binary_search_tree.c -o binary_search_tree.o $(flags)

tests.o: tests.c binary_search_tree.h
	gcc -c tests.c -o tests.o $(flags)

io: io.c
	gcc io.c -o io $(flags)

clean:
	rm -f tests $(objects)
