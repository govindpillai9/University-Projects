#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "misc.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "hi:o:"
//helper functions to deal with and get nibbles of a byte
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
    bool input = false;
    bool output = false;
    FILE *fp = stdout;
    FILE *inputp = stdin;
    //options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 'i':
            input = true;
            inputp = fopen(optarg, "r");
            break;
        case 'o':
            output = true;
            fp = fopen(optarg, "w");
            break;
        }
    }
    //prints help summary if requested
    if (help) {
        printf("SUMMARY\n");
        printf("   creates a (8,4) Hamming code\n");
        printf("HOW TO USE\n");
        printf("   ./encode [-h] [-i infile] [-o outfile]\n");
        printf("OPTIONS\n");
        printf("   -h: Help menu to use program\n");
        printf("   -i: File to receive data\n");
        printf("   -o: File to print data\n");
        return 0;
    }
    //creates G Matrix
    BitMatrix *gen = bm_create(4, 8);
    for (uint32_t i = 0; i < 8; i++) {
        for (uint32_t j = 0; j < 4; j++) {
            if (i < 4) {
                if (i == j) {
                    bm_set_bit(gen, j, i);
                } else {
                    bm_clr_bit(gen, j, i);
                }
            } else {
                if (i - j == 4) {
                    bm_clr_bit(gen, j, i);
                } else {
                    bm_set_bit(gen, j, i);
                }
            }
        }
    }
    //reads a byte of the data at a time and splits them into 2 nibbles
    //each nibble is used to make a code
    while ((c = fgetc(inputp)) != EOF) {
        uint8_t code1 = encode(gen, lower_nibble(c));
        fputc(code1, fp);
        uint8_t code2 = encode(gen, upper_nibble(c));
        fputc(code2, fp);
    }
    if (input) {
        fclose(inputp);
    }
    if (output) {
        fclose(fp);
    }

    bm_delete(&gen);
}
