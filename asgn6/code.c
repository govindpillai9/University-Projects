#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "code.h"
#include "defines.h"
Code code_init(void) {
	Code c;
	c.top = 0;
	return c;
}

uint32_t code_size(Code *c) {
	return c->top;
}

bool code_empty(Code *c) {
	return c->top == 0;
}

bool code_full(Code *c) {
	return c->top == ALPHABET;
}

bool code_push_bit(Code *c, uint8_t bit) {
        if (code_full(c)) {
                return false;
        }
	if(bit == 1) {
		c->bits[c->top/8] |= (1 << (c->top % 8));
	}
	if(bit == 0) {
		c->bits[c->top/8] &= ~(1 << (c->top % 8));
	}
        c->top += 1;
        return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
        if (code_empty(c)) {
		return false;
        }
        c->top -= 1;
	uint8_t val = (c->bits[c->top/8]) & (1 << (c->top % 8));
        *bit = val >> (c->top % 8);
        return true;

}

void code_print(Code *c) {
	for (uint32_t i = 0; i < c->top; i++) {
		uint8_t val = (c->bits[i/8]) & (1 << (i % 8));
        	printf("%d ",(val >> (i % 8)));
    	}
    	printf("\n");

}

