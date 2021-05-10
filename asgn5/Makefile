CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra

all: encode decode entropy error

encode: encode.o hamming.o bv.o bm.o
	$(CC) $(CFLAGS) -o encode encode.o hamming.o  bv.o bm.o -lm

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c

decode: decode.o hamming.o bv.o bm.o misc.o
	$(CC) $(CFLAGS) -o decode decode.o hamming.o bv.o bm.o misc.o -lm
decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c
hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c
bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c
bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c
misc.o: misc.c
	$(CC) $(CFLAGS) -c misc.c

entropy: entropy.o
	$(CC) $(CFLAGS) -o entropy entropy.o -lm

entropy.o: entropy.c
	$(CC) $(CFLAGS) -c entropy.c

error: error.o
	$(CC) $(CFLAGS) -o error error.o -lm
error.o: error.c
	$(CC) $(CFLAGS) -c error.c
clean: 
	rm -f *.o encode decode entropy error
format:
	clang-format -i -style=file *.h *.c
