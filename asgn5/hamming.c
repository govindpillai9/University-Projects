#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bm.h"

uint8_t lookup[16] = {0,4,5,HAM_ERR,6,HAM_ERR,HAM_ERR,3,7,HAM_ERR,HAM_ERR,2,HAM_ERR,1,0,HAM_ERR};

uint8_t encode(BitMatrix *G, uint8_t msg) {
	BitMatrix *mg = bm_from_data_(lower_nibble(msg), 4);
	BitMatrix *C = bm_multiply(mg, G);
	return bm_to_data(C);

}

HAM_STATUS decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
	BitMatrix *cd =bm_from_data(code,8);
	BitMatrix *e = bm_multiply(cd,Ht);
	uint8_t current = bm_to_data(e);
	if(current == 0) {
		*msg = lower_nibble(code);
		return HAM_OK;
	}else{
		uint8_t element = lookup[current];
		if(element == HAM_ERR) {
			*msg = lower_nibble(code);
			return HAM_ERR;
		}
		*msg = code ^ (1 << element);
		return HAM_CORRECT;
	}
}

uint8_t lower_nibble(uint8_t val) {
	return val & 0xF;
}

uint8_t upper_nibble(uint8_t val) {
	return val >> 4;
}

uint8_t pack_byte(uint8_t upper, uint8_t lower) {
	return (upper << 4) | (lower & 0xF);
}
