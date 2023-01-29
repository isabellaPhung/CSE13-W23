SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = mathlib-test.o e.o madhava.o euler.o bbp.o viete.o newton.o

all: mathlib-test

mathlib-test: $(OBJS) 
	clang $(OBJS) -o mathlib-test -lm

mathlib-test.o: mathlib-test.c e.c madhava.c euler.c bbp.c viete.c newton.c mathlib.h
	clang $(CFLAGS) -c mathlib-test.c -o mathlib-test.o	

e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c -o e.o

madhava.o: madhava.c mathlib.h
	clang $(CFLAGS) -c madhava.c -o madhava.o

euler.o: euler.c mathlib.h
	clang $(CFLAGS) -c euler.c -o euler.o

bbp.o: bbp.c mathlib.h
	clang $(CFLAGS) -c bbp.c -o bbp.o

viete.o: viete.c mathlib.h
	clang $(CFLAGS) -c viete.c -o viete.o

newton.o: newton.c mathlib.h
	clang $(CFLAGS) -c newton.c -o newton.o

clean:
	rm -f *.o

format:
	clang-format -i -style=file *.[ch]
