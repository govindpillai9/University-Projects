#Assignment 7

This program takes in an input from stdin and filters out all the badspeak and oldspeak words in the file. Depending on the command line arguments given by the user, the size of the bloom filter and hash table used to filter and find bad words will vary, the move-to-front option for the linked lists used in the hash table will be turned on/off, and the program may print the program statistics to stdout. The program will list out the bad words, and old words used in the input file, as well as the new translations for the old words.
## Build

	$ make 
	
## Running

	$ ./encode -(command) < (input file)
	
	COMMANDS (encode):
	h: help
	t: hash table size (default = 10000)
	o: bloom filter size (default = 2^20)
	m: move-to-front enabled
	s: program statistics
## Cleaning
	$ make clean
	
## Formatting
	$ make format
