flags = -Wall -Werror -Wextra -pedantic -g
objects = integers.o tests.o

test: tests
	./tests

tests: $(objects)
	gcc $(objects) -o tests $(flags)

tests.o: tests.c integers.h
	gcc -c tests.c $(flags)

integers.o: integers.c integers.h
	gcc -c integers.c $(flags)

clean:
	rm -f tests $(objects)
