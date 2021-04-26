#Assignment 3

This program takes in command line inputs from the user. Depending on the input the program
will either sort a random array using bubble_sort(array, size), shell_sort(array, size), quick_sort_stack(array, size), or quick_sort_queue(array,size). The program will print
out the sort that was called, the statitics of that sort, and the sorted elements of the array. If quick_sort is called, the max size of the stack/queue is also printed.

## Build

	$ make sorting
	
## Running

	$ ./sorting -(command)
	
	COMMANDS:
	a: all
	b: bubble_sort
	s: shell_sort
	q: quick_sort_stack
	Q: quick_sort_queue
	r: enter random seed (default = 13371453)
	n: enter size of array (default = 100)
	p: enter number of elements to be printed (default = 100)
	
## Cleaning
	$ make clean
	
## Formatting
	$ make format
