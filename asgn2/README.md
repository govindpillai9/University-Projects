#Assignment 2

This program takes in command line inputs from the user. Depending on the input the program
will either evaluate arcsin(x) on the interval [-1,1), arccos(x) on the interval [-1,1), arctan(x) on the interval [1,10), or ln(x) on the interval [1, 10). The program will print
out each x value with a step of 0.1, the value of the implemented function within the program, 
the value of the function in the math.h library, and the difference between the implemented
function and the math.h function. 

## Build

	$ make ./mathlib-test
## Running

	$ ./mathlib-test -(command)
	
	COMMANDS:
	a: all
	s: arcsin
	c: arccos
	t: arctan
	l: ln
	
## Cleaning
	$ make clean
	
	 
