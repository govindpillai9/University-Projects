#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bv.h"
#include "bm.h"
#include "hamming.h"
#include <unistd.h>
#include <string.h>
#define OPTIONS "hi:o:"
uint8_t lower_nibble(uint8_t val) {
        return val & 0xF;
}

uint8_t upper_nibble(uint8_t val) {
        return val >> 4;
}

uint8_t pack_byte(uint8_t upper, uint8_t lower) {
        return (upper << 4) | (lower & 0xF);
}
int main(int argc, char **argv) {
	int c = 0;
	int opt = 0;
	bool help = false;
	FILE *fp = stdout;
	FILE *inputp = stdin;
	while((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch(opt) {
			case 'h':
				help = true;
				break;
			case 'i':
				inputp = fopen(optarg, "r");
				break;
			case 'o':
				fp = fopen(optarg, "w");
				break;
		}
	}
	BitMatrix *gen = bm_create(4,8);
	for(uint32_t i = 0; i < 8; i++) {
		for(uint32_t j = 0; j < 4; j++) {
			if(i < 4) {
				if(i == j) {
					bm_set_bit(gen,j,i);
				}else{
					bm_clr_bit(gen,j,i);
				}
			}else{
				if(i-j == 4) {
					bm_clr_bit(gen,j,i);
				}else{
					bm_set_bit(gen,j,i);
				}
			}
		}
	}
	while((c = fgetc(inputp)) != EOF) {
		uint8_t code1 = encode(gen, lower_nibble(c));
		fputc(code1, fp);
		uint8_t code2 = encode(gen, upper_nibble(c));
		fputc(code2, fp);
	}
}
