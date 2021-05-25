CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode decode entropy


encode: encode.o node.o pq.o stack.o code.o io.o huffman.o 
	$(CC) $(CFLAGS) -o encode encode.o node.o pq.o stack.o code.o io.o huffman.o -lm
decode: decode.o node.o pq.o stack.o code.o io.o huffman.o 
	$(CC) $(CFLAGS) -o decode decode.o node.o pq.o stack.o code.o io.o huffman.o -lm
entropy: entropy.o
	$(CC) $(CFLAGS) -o entropy entropy.o -lm
decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c
encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c
entropy.o: entropy.c
	$(CC) $(CFLAGS) -c entropy.c
test.o: test.c
	$(CC) $(CFLAGS) -c test.c
entropy.o: entropy.c
	$(CC) $(CFLAGS) -c entropy.c
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
format:
	clang-format -i -style=file *.h *.c
