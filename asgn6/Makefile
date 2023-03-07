SHELL := /bin/sh
CC = clang-15
CFLAGS = -Wall -Wpedantic -Werror -Wextra 
OBJS = io.o encode.o decode.o trie.o word.o

all: encode decode

encode: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o encode -lm

decode: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o decode -lm

encode.o: encode.c trie.c io.c
	$(CC) $(CFLAGS) -c encode.c -o encode.o	

decode.o: decode.c word.c io.c
	$(CC) $(CFLAGS) -c encode.c -o encode.o	

trie.o: trie.c code.h
	$(CC) $(CFLAGS) -c trie.c -o trie.o

word.o: word.c code.h
	$(CC) $(CFLAGS) -c word.c -o word.o

io.o: io.c code.h
	$(CC) $(CFLAGS) -c io.c -o io.o

clean:
	rm -f *.o
	rm encode
	rm decode

format:
	clang-format-15 -i -style=file *.[ch]
