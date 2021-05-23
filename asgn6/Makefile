CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: test

test: test.o node.o pq.o stack.o code.o io.o huffman.o
	$(CC) $(CFLAGS) -o test test.o node.o pq.o stack.o code.o io.o huffman.o -lm

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c

clean:
	rm -f *.o test
