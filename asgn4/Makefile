SHELL := /bin/sh
CC = clang-15
CFLAGS = -Wall -Wpedantic -Werror -Wextra 
OBJS = universe.o 

all: life

life: $(OBJS) 
	$(CC) $(OBJS) -o life -lm

life.o: life.c universe.c
	$(CC) $(CFLAGS) -c life.c -o life

universe.o: universe.c universe.h
	$(CC) $(CFLAGS) -c universe.c -o universe.o

clean:
	rm -f *.o
	rm life

format:
	clang-format-15 -i -style=file *.[ch]
