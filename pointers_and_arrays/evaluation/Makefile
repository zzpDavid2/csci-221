flags = -Wall -Werror -Wextra -pedantic -g

objects = binary_search_tree.o io.o

tests: binary_search_tree.o io.o
	gcc $(objects) -o tests $(flags)
	./tests test1 test2 test3

binary_search_tree.o: binary_search_tree.c
	gcc -c binary_search_tree.c -o binary_search_tree.o $(flags)

io.o: io.c
	gcc -c io.c -o io.o $(flags)

clean:
	rm -f tests $(objects)
