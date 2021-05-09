#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bv.h"
#include "bm.h"
typedef struct BitMatrix {
	uint32_t rows;
	uint32_t cols;
	BitVector *vector;
}BitMatrix;

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
	BitMatrix *m = (BitMatrix *) malloc(sizeof(BitMatrix));
	m->rows = rows;
	m->cols = cols;
	m->vector = bv_create(rows*cols);
}

void bm_delete(BitMatrix **m) {
    if (*m && (*m)->vector) {
        bv_delete((*m)->vector);
        free(*m);
        *m = NULL;
    }
    return;
}

uint32_t bm_rows(BitMatrix *m) {
	return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
	return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
	bv_set_bit(m->vector,r*(m->cols)+c);
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
	bv_clr_bit(m->vector,r*(m->cols)+c);
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
	bv_get_bit(m->vector,r*(m->cols)+c);
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
	BitMatrix *matrix = bm_create(1,length);
	for(uint32_t i = 0; i < length; i++) {
		if(byte & (1 << i)) {
			bm_set_bit(matrix,0,i);
		}else{
			bm_clr_bit(matrix,0,i);
		}
	}
}

uint8_t bm_to_data(BitMatrix *m) {
	uint8_t value = 0;
	for(uint32_t i = 0; i < m->cols; i++) {
		value ^= bv_get_bit(m->vector,i);
	}
	return value;
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
	BitMatrix *pointer = bm_create(A->rows,B->cols);
	for(uint32_t i = 0; i < A->rows; i++) {
		for(uint32_t j = 0; j < B->cols; j++) {
			uint8_t sum = 0;
			for(uint32_t k = 0; k < A->cols; k++) {
				sum ^= (bm_get_bit(A, i, k) & bm_get_bit(B, k, i));
			}
			bm_set_bit(pointer, i, j);

		}
	}
}

void bm_print(BitMatrix *m) {
	printf("[");
}

