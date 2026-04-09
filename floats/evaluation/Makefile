flags = -std=c2x -Wall -Wextra -pedantic -g
objects = tiny_float.o tests.o

test: tests
	./tests

tests: $(objects)
	gcc $(objects) -o tests $(flags) -lm

tests.o: tests.c tiny_float.h
	gcc -c tests.c $(flags)

tiny_float.o: tiny_float.c tiny_float.h
	gcc -c tiny_float.c $(flags)

clean:
	rm -f tests $(objects)
