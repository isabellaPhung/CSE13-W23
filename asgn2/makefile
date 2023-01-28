SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: mathlib-test

mathlib-test: mathlib-test.o e.o madhava.o euler.o bbp.o viete.o newton.o
	clang mathlib-test.o e.o madhava.o euler.o bbp.o viete.o newton.o -o mathlib-test

mathlib-test.o: mathlib-test.c e.c madhava.c euler.c bbp.c viete.c newton.c
	clang $(CFLAGS) -c mathlib-test.c -o mathlib-test.o
	clang $(CFLAGS) -c madhava.c -o madhava.o
	clang $(CFLAGS) -c euler.c -o euler.o
	clang $(CFLAGS) -c bbp.c -o bbp.o
	clang $(CFLAGS) -c viete.c -o newton.o 

clean:
	rm -f *.o

format:
	clang-format -i -style=file *.[ch]
