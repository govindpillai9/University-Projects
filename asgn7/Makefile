CC = clang
CFLAGS = -Wall -Wextra -Wpedantic

all: test

test: test.o bv.o bf.o speck.o
	$(CC) $(CFLAGS) -o test test.o bv.o bf.o speck.o -lm

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c
