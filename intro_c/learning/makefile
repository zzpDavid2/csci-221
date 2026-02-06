objects = array.o
flags = -Wall -Werror -Wextra -pedantic

#test targets
test : hello_world roster_test
	./hello_world
	./roster_test

#hello world
hello_world : hello_world.c array.o
	gcc hello_world.c -o hello_world $(objects) $(flags)

array.o : array.c array.h
	gcc -c array.c $(flags)

#roster test
roster_test : roster_test.c roster.h
	gcc roster_test.c -o roster_test $(flags)

clean :
	rm -f hello_world array roster_test $(objects)
