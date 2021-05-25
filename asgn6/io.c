#include "io.h"

#include "code.h"
#include "defines.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static uint32_t bit_index_w = 0;
static uint32_t bit_index_r = 0;
static uint8_t buffer_write[BLOCK];
static uint8_t buffer_read[BLOCK];
uint64_t bytes_read = 0;
uint64_t bytes_written = 0;
//reads nbytes number of bytes into buf from the infile
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total = 0;
    int bytes = 1;
    while (bytes > 0 && (total != nbytes)) {
        bytes = read(infile, buf, nbytes);
        total += bytes;
        bytes_read += total;
    }
    return total;
}
//writes nbytes number of bytes to the outfile from the buf
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0;
    int bytes = 1;
    while (bytes > 0 && (total < nbytes)) {
        bytes = write(outfile, buf, nbytes);
        total += bytes;
        bytes_written += total;
    }
    return total;
}
static bool not_read = true;
//reads from the infile one bit at a time
bool read_bit(int infile, uint8_t *bit) {
    uint32_t eof = 0;
    uint32_t bytes = 0;
    if (not_read || bit_index_r >= BLOCK * 8) {
        bit_index_r = 0;
        /*for (uint64_t i = 0; i < BLOCK; i++) {
			buffer_read[i] = 0;
		}*/
        bytes = read_bytes(infile, buffer_read, BLOCK);
        not_read = false;
    }
    if (bytes != BLOCK) {
        eof = bytes * 8;
    }
    uint8_t val = (buffer_read[bit_index_r / 8]) & (1 << (bit_index_r % 8));
    *bit = val >> (bit_index_r % 8);
    bit_index_r++;
    return bit_index_r < eof;
}
//writes the given code to the outfile
void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i++) {
        uint8_t val = (c->bits[i / 8]) & (1 << (i % 8));
        uint8_t bit = val >> (i % 8);

        if (bit == 1) {
            buffer_write[bit_index_w / 8] |= (1 << (bit_index_w % 8));
        } else if (bit == 0) {
            buffer_write[bit_index_w / 8] &= ~(1 << (bit_index_w % 8));
        }
        bit_index_w += 1;
        if (bit_index_w == 8 * BLOCK) {
            write_bytes(outfile, buffer_write, BLOCK);
            bit_index_w = 0;
        }
    }
}
//writes anything remaining in the buffer to the outfile
void flush_codes(int outfile) {
    int numbytes = (bit_index_w) / 8;
    if (bit_index_w % 8 == 0) {
        numbytes++;
    }
    write_bytes(outfile, buffer_write, numbytes);
}
