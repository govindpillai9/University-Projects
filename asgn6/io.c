#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "node.h"
#include "io.h"
#include "code.h"
#include "pq.h"
#include "stack.h"
#include "defines.h"
static uint32_t bit_index = 0;
static uint8_t buffer[BLOCK];
int read_bytes(int infile, uint8_t *buf, int nbytes) {
	int total = 0;
	int bytes = 1;
	while(bytes > 0 && (total != nbytes)) {
		bytes = read(infile,buf,nbytes);
		total += bytes;
	}
	return total;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
	int total = 0;
	int bytes = 1;
	while(bytes > 0 && (total != nbytes)) {
		bytes = write(outfile,buf,nbytes);
		total += bytes;
	}
	return total;
}

bool read_bit(int infile, uint8_t *bit) {
	uint32_t eof = 0;
	uint32_t bytes = read_bytes(infile, buffer, BLOCK);
	if(bytes != BLOCK) {
		eof = bytes * 8;
	}
	*bit = (buffer[bit_index/8]) & (1 << (bit_index % 8));
	bit_index = (bit_index + 1) % BLOCK * 8;	
	return bit_index < eof;
}

void write_code(int outfile, Code *c) {
	for(uint32_t i = 0; i < code_size(c); i++) {
		uint8_t bit = (buffer[bit_index/8]) & (1 << (bit_index % 8));
		if(bit == 1) {
			buffer[bit_index/8] |= (1 << (bit_index % 8));
		}
		else if(bit == 0) {
			buffer[bit_index/8] &= ~(1 << (bit_index % 8));
		}
		bit_index += 1;
		if(bit_index == 8*BLOCK) {
			write_bytes(outfile,buffer,BLOCK);
			bit_index = 0;
		}else{
			flush_codes(outfile);
		}
	}
}

void flush_codes(int outfile) {
	int numbytes = (bit_index + 1)/8;
	write_bytes(outfile,buffer,numbytes);
}

