flags = -Wall -Werror -Wextra -pedantic -g
objects = moving.o powers.o distance.o weekday.o

test : tests.c $(objects)
	gcc tests.c -o tests $(objects) $(flags)
	./tests

moving.o : moving.c
	gcc -c moving.c $(flags)

powers.o : powers.c powers.h
	gcc -c powers.c $(flags)

distance.o : distance.c distance.h
	gcc -c distance.c $(flags)

weekday.o : weekday.c weekday.h
	gcc -c weekday.c $(flags)

clean :
	rm -f tests $(objects)