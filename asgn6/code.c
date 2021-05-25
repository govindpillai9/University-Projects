#include "code.h"

#include "defines.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//creates code
Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
    }
    return c;
}
//returns code size
uint32_t code_size(Code *c) {
    return c->top;
}
//returns true if code is empty
bool code_empty(Code *c) {
    return c->top == 0;
}
//returns true if code is full
bool code_full(Code *c) {
    return c->top == ALPHABET;
}
//returns true if a bit was successfully pushed onto the code
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    if (bit == 1) {
        c->bits[c->top / 8] |= (1 << (c->top % 8));
    }
    if (bit == 0) {
        c->bits[c->top / 8] &= ~(1 << (c->top % 8));
    }
    c->top += 1;
    return true;
}
//returns true if a bit was successfully popped off the code
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    c->top -= 1;
    uint8_t val = (c->bits[c->top / 8]) & (1 << (c->top % 8));
    *bit = val >> (c->top % 8);
    return true;
}
//prints code
void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        uint8_t val = (c->bits[i / 8]) & (1 << (i % 8));
        printf("%d ", (val >> (i % 8)));
    }
    printf("\n");
}
