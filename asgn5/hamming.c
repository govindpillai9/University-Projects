#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bm.h"
#include "hamming.h"
#include "misc.h"
int lookup[16] = {0,4,5,HAM_ERR,6,HAM_ERR,HAM_ERR,3,7,HAM_ERR,HAM_ERR,2,HAM_ERR,1,0,HAM_ERR};
int uncorrected;
int corrected;
uint8_t encode(BitMatrix *G, uint8_t msg) {
	BitMatrix *mg = bm_from_data(msg, 4);
	BitMatrix *C = bm_multiply(mg, G);
	return bm_to_data(C);

}

HAM_STATUS decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
	BitMatrix *cd =bm_from_data(code,8);
	BitMatrix *e = bm_multiply(cd,Ht);
	uint8_t current = bm_to_data(e);
	if(current == 0) {
		*msg = code;
		return HAM_OK;
	}else{
		int element = lookup[current];
		if(element == HAM_ERR) {
			*msg = code;
			uncorrected++;
			return HAM_ERR;
		}
		*msg = code ^ (1 << element);
		corrected++;
		return HAM_CORRECT;
	}
}


