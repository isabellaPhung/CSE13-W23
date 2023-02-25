SHELL := /bin/sh
CC = clang-15
CFLAGS = -Wall -Wpedantic -Werror -Wextra $(pkg-config -libs gmp)
OBJS = numtheory.o ss(.)o

all: keygen decryptor encryptor

decrypt: decryptor

encrypt: encryptor

keygen: keygen

keygen: $(OBJS) keygen.o 
	$(CC) $(OBJS) -o keygen -lm

keygen.o: keygen.c ss.c numtheory.c
	$(CC) $(CFLAGS) -c keygen.c -o keygen.o	

encryptor: $(OBJS) encryptor.o 
	$(CC) $(OBJS) -o encryptor -lm

encryptor.o: encryptor.c ss.c numtheory.c
	$(CC) $(CFLAGS) -c encryptor.c -o encryptor.o	

decryptor: $(OBJS) decryptor.o 
	$(CC) $(OBJS) -o decryptor -lm

decryptor.o: decryptor.c ss.c numtheory.c
	$(CC) $(CFLAGS) -c decryptor.c -o decryptor.o	

numtheory.o: numtheory.c
	$(CC) $(CFLAGS) -c numtheory.c -o numtheory.o

ss.o: ss.c
	$(CC) $(CFLAGS) -c ss.c -o ss.o

clean:
	rm -f *.o
	rm keygen
	rm decryptor
	rm encryptor

format:
	clang-format-15 -i -style=file *.[ch]
