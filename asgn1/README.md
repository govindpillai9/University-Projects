# Assignment 1

This program takes in 2 inputs: a nonegative random seed and the number of players
inclusively bounded at 1 and 14. Each player starts off with 3 dollars and takes turns
rolling a die moving to the right. Based on what the player rolls, they will either have
to give a dollar to the player on their left or right, the pot, or do nothing at all. The
program uses the random seed and number of player inputs to simulate and print the transactions
until there is only one player left with money.

## Build

	$ clang -Wall -Wextra -Werror -Wpedantic -o lrc lrc.o
	OR
	$ make lrc
## Running

	$ ./lrc
	
## Cleaning
	
	$ rm -f lrc lrc.o
	OR
	$ make lrc
