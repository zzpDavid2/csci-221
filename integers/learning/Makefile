flags = -Wall -Werror -Wextra -pedantic -g

test: integers
	./integers

integers: integers.c
	gcc integers.c -o integers $(flags)

clean:
	rm -f integers
