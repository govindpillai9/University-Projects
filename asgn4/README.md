#Assignment 4

This program takes in command line inputs from the user. Depending on the input the program
will find the hamiltonian path of a graph, given the number of vertices and edges of those vertices in a file. The program will print out the length of the hamiltonian stack (the sum of 
the weights of the edges on the graph), the path itself, and the number of recursive calls.

## Build

	$ make tsp
	
## Running

	$ ./tsp -(command)
	
	COMMANDS:
	h: help
	v: verbose mode
	u: undirected mode
	i: input file (default = stdin)
	o: output file (default = stdout)
	
## Cleaning
	$ make clean
	
## Formatting
	$ make format
