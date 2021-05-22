CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: test

test: test.o node.o pq.o
	$(CC) $(CFLAGS) -o test test.o node.o pq.o -lm

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c
clean:
	rm -f *.o test
