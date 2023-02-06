SHELL := /bin/sh
CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra 
OBJS = set.o shell.o sorting.o stats.o quick.o heap.o batcher.o

all: sorting

sorting: $(OBJS) 
	$(CC) $(OBJS) -o sorting -lm

sorting.o: sorting.c set.c shell.c stats.c quick.c heap.c batcher.c gaps.h
	$(CC) $(CFLAGS) -c sorting.c -o sorting.o	

set.o: set.c
	$(CC) $(CFLAGS) -c set.c -o set.o

shell.o: shell.c gaps.h
	$(CC) $(CFLAGS) -c shell.c -o shell.o

stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c -o stats.o

quick.o: quick.c 
	$(CC) $(CFLAGS) -c quick.c -o quick.o

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c -o heap.o

batcher.o: batcher.c
	$(CC) $(CFLAGS) -c batcher.c -o batcher.o

clean:
	rm -f *.o
	rm sorting

format:
	clang-format -i -style=file *.[ch]
