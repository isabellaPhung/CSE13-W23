SHELL := /bin/sh
CC = clang-15
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g -gdwarf-4 -ggdb3
OBJS = io.o trie.o word.o

all: encode decode

encode: $(OBJS) encode.o
	$(CC) $(CFLAGS) $(OBJS) encode.c -o encode -lm

decode: $(OBJS) decode.o
	$(CC) $(CFLAGS) $(OBJS) decode.c -o decode -lm

encode.o: encode.c trie.c io.c
	$(CC) $(CFLAGS) -c encode.c -o encode.o	

decode.o: decode.c word.c io.c
	$(CC) $(CFLAGS) -c decode.c -o decode.o	

trie.o: trie.c code.h
	$(CC) $(CFLAGS) -c trie.c -o trie.o

word.o: word.c code.h
	$(CC) $(CFLAGS) -c word.c -o word.o

io.o: io.c
	$(CC) $(CFLAGS) -c io.c -o io.o

clean:
	rm -f *.o
	rm encode
	rm decode

format:
	clang-format-15 -i -style=file *.[ch]
