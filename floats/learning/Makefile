flags = -Wall -Werror -Wextra -pedantic -g

test: floats
	./floats

floats: floats.c
	gcc floats.c -o floats $(flags)

clean:
	rm -f floats
