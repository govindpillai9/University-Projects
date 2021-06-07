CC = clang
CFLAGS = -Wall -Wextra -Wpedantic

all: banhammer

banhammer: banhammer.o bv.o bf.o speck.o node.o ll.o ht.o parser.o
	$(CC) $(CFLAGS) -o banhammer banhammer.o bv.o bf.o speck.o node.o ll.o ht.o parser.o -lm

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c
