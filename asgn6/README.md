#Assignment 6

This program takes in command line inputs from the user. Depending on the input the program 
will encode, decode, or display the statistics of the data compression. The encoder
will compression the file using Huffman coding. The decoder will use the huffman codes along with a tree dump to decode it. Entropy will display the entropy of any given file.
## Build

	$ make 
	
## Running

	$ ./encode -(command) |./decode -(command)
	
	COMMANDS (encode):
	h: help
	i: input file (default = stdin)
	o: output file (default = stdout)
	v: compression stats
	COMMANDS (decode):
	h: help
	i:input file (default = stdin)
	o: output file(default = stdout)
	v: compression stats
	COMMANDS(entropy):
	h: help
## Cleaning
	$ make clean
	
## Formatting
	$ make format
