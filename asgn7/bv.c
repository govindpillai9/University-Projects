#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BitVector {
    uint32_t length;
    uint8_t *vector;
} BitVector;

//creates the vector
BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    if (v) {
        v->length = length;
        if (length > 0) {
            //from Sahiti's Lab Section
            uint32_t val = length % 8 == 0 ? length / 8 : length / 8 + 1;
            v->vector = (uint8_t *) calloc(val, sizeof(uint8_t));
        }
        if (!v->vector) {
            free(v);
            v = NULL;
        }
    }
    return v;
}
//deletes the vector
void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) {
        free((*v)->vector);
        free(*v);
        *v = NULL;
    }
    return;
}
//returns the length of the vector
uint32_t bv_length(BitVector *v) {
    return v->length;
}

//sets a bit in the vector
void bv_set_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] |= (1 << (i % 8));
}
//clear a bit in the vector
void bv_clr_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] &= ~(1 << (i % 8));
}
//gets bit from the vector
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    uint8_t result = (v->vector[i / 8]) & (1 << (i % 8));
    return result >> (i % 8);
}
//print the vector
void bv_print(BitVector *v) {
    printf("Bit Vector: [");
    for (uint32_t i = 0; i < v->length; i++) {
        printf("%d", bv_get_bit(v, i));
        if (i < v->length - 1) {
            printf(", ");
        }
    }
    printf("]");
    printf("\n");
}
