#Assignment 5

This program takes in command line inputs from the user. Depending on the input the program 
will encode, decode, produce errors, or display the entropy of given data in a file. The encoder
will create a Hamming code to encode the data. The decoder will use the hamming code along with
other matrices to decode it. Errors.c will produce "noise" or errors in the file for the decoder
to fix. Entropy will display the entropy of any given file.
## Build

	$ make 
	
## Running

	$ ./encode -(command) |./decode -(command)|./error -(command)|./entropy -(command)
	
	COMMANDS (encode):
	h: help
	i: input file (default = stdin)
	o: output file (default = stdout)
	COMMANDS (decode):
	h: help
	i:input file (default = stdin)
	o: output file(default = stdout)
	COMMANDS(error):
	h: help
	e: error injection
	s: random seed
	COMMANDS(entropy):
	h: help
## Cleaning
	$ make clean
	
## Formatting
	$ make format
