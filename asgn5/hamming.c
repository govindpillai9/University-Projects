#include "hamming.h"

#include "bm.h"
#include "misc.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//lookup table
int lookup[16]
    = { 0, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2, HAM_ERR, 1, 0, HAM_ERR };
uint8_t encode(BitMatrix *G, uint8_t msg) {
    //creates matrix out of message
    BitMatrix *mg = bm_from_data(msg, 4);
    //multipies the new matrix with G
    BitMatrix *C = bm_multiply(mg, G);
    //creates a code and returns it
    uint8_t data = bm_to_data(C);
    bm_delete(&C);
    bm_delete(&mg);
    return data;
}

HAM_STATUS decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    //creates matrix from given code
    BitMatrix *cd = bm_from_data(code, 8);
    //multiplies the new matrix with H transpose
    BitMatrix *e = bm_multiply(cd, Ht);
    //gets a message
    uint8_t current = bm_to_data(e);
    bm_delete(&cd);
    bm_delete(&e);
    //if the message is 0 do nothing
    if (current == 0) {
        *msg = code;
        return HAM_OK;
    } else {
        //if the message is not in the lookup table return HAM_ERR
        int element = lookup[current];
        if (element == HAM_ERR) {
            *msg = code;
            return HAM_ERR;
        }
        //otherwise correct the error and return HAM_CORRECT
        *msg = code ^ (1 << element);
        return HAM_CORRECT;
    }
}
