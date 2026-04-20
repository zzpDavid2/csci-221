flags = -Wall -Werror -Wextra -pedantic -g

test: decaying_sum
	./decaying_sum

decaying_sum: decaying_sum.c decaying_sum.h
	gcc $(flags) -o $@ $<

clean:
	rm -f decaying_sum
