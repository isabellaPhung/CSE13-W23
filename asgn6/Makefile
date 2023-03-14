SHELL := /bin/sh
CC = clang-15
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g -gdwarf-4 -ggdb3
OBJS = trie.o io.o

all: test

test: $(OBJS) test.o
	$(CC) $(CFLAGS) $(OBJS) test.c -o test -lm

trie.o: trie.c code.h
	$(CC) $(CFLAGS) -c trie.c -o trie.o

io.o: io.c
	$(CC) $(CFLAGS) -c io.c -o io.o

clean:
	rm -f *.o
	rm encode
	rm decode

format:
	clang-format-15 -i -style=file *.[ch]
