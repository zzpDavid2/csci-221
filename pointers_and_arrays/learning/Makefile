flags = -Wall -Werror -Wextra -pedantic -g

test: pointers
	./pointers test1 test2 test3

pointers: pointers.c
	gcc pointers.c -o pointers $(flags)

clean:
	rm -f pointers
