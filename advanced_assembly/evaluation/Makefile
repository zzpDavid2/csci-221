CC = gcc
CFLAGS = -Wall -Wextra -std=c11

decaying_sum: decaying_sum.c
	$(CC) $(CFLAGS) -o $@ $<

test: decaying_sum
	./decaying_sum

clean:
	rm -f decaying_sum

.PHONY: test clean
