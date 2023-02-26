SHELL := /bin/sh
CC = clang-15
CFLAGS = -Wall -Wpedantic -Werror -Wextra -g -gdwarf-4 -ggdb3 
GMP = $(shell pkg-config --libs gmp)

OBJS = numtheory.o ss.o randstate.o

all: keygen decryptor encryptor

keygen: $(OBJS) keygen.o 
	$(CC) $(CFLAGS) $(OBJS) keygen.c -o keygen -lm $(GMP)

keygen.o: keygen.c ss.c numtheory.c randstate.c numtheory.h ss.h
	$(CC) $(CFLAGS) -c keygen.c -o keygen.o	

encryptor: $(OBJS) encryptor.o 
	$(CC) $(CFLAGS) $(OBJS) encryptor.c -o encryptor -lm $(GMP)

encryptor.o: encryptor.c ss.c numtheory.c randstate.c numtheory.h ss.h
	$(CC) $(CFLAGS) -c encryptor.c -o encryptor.o	

decryptor: $(OBJS) decryptor.o 
	$(CC) $(CFLAGS) $(OBJS) decryptor.c -o decryptor -lm $(GMP)

decryptor.o: decryptor.c ss.c numtheory.c randstate.c numtheory.h ss.h
	$(CC) $(CFLAGS) -c decryptor.c -o decryptor.o	

numtheory.o: numtheory.c numtheory.h
	$(CC) $(CFLAGS) -c numtheory.c -o numtheory.o

ss.o: ss.c ss.h
	$(CC) $(CFLAGS) -c ss.c -o ss.o

clean:
	rm -f *.o
	rm keygen
	rm decryptor
	rm encryptor

format:
	clang-format-15 -i -style=file *.[ch]
