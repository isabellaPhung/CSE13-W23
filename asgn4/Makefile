SHELL := /bin/sh
CC = clang-15
GCC = gcc
GFLAGS = -g -gdwarf-4 -ggdb3
CFLAGS = -Wall -Wpedantic -Werror -Wextra
OBJS = life.o universe.o

all: life

life: $(OBJS)
	$(GCC) $(GFLAGS) $(OBJS) -lncurses -lm -o life

life.o: life.c universe.c universe.h
	$(GCC) $(GFLAGS) -c life.c -o life.o

universe.o: universe.c universe.h
	$(GCC) $(GFLAGS) -c universe.c -o universe.o

clean:
	rm -f *.o
	rm life

format:
	clang-format-15 -i -style=file *.[ch]
