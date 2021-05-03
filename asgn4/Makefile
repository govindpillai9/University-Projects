CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: tsp

tsp: tsp.o graph.o stack.o path.o

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c

clean:
	rm -f *.o tsp

format:
	clang-format -i -style=file *.h *.c
