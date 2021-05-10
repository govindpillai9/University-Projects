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
#define OPTIONS "hi:o:v"
//helper functions to deal with and get nibbles from a byte
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
    int correct = 0;
    float incorrect = 0;
    float totBytes = 0;
    uint8_t msg1 = 0;
    uint8_t msg2 = 0;
    HAM_STATUS status = 0;
    int c = 0;
    int opt = 0;
    bool help = false;
    bool input = false;
    bool output = false;
    bool stats = false;
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
        case 'v': stats = true; break;
        }
    }
    //prints help summary if requested
    if (help) {
        printf("SUMMARY\n");
        printf("   decodes a code using a parity-checker\n");
        printf("HOW TO USE\n");
        printf("   ./decode [-h] [-i infile] [-o outfile] [-v]\n");
        printf("OPTIONS\n");
        printf("   -h: Help menu to use program\n");
        printf("   -i: File to receive data\n");
        printf("   -o: File to print data\n");
        printf("   -v: Prints statistics of the decoder\n");
        return 0;
    }
    //creates H transpose matrix
    BitMatrix *ht = bm_create(8, 4);
    for (uint32_t i = 0; i < 8; i++) {
        for (uint32_t j = 0; j < 4; j++) {
            if (i < 4) {
                if (i == j) {
                    bm_clr_bit(ht, i, j);
                } else {
                    bm_set_bit(ht, i, j);
                }
            } else {
                if (i - j == 4) {
                    bm_set_bit(ht, i, j);
                } else {
                    bm_clr_bit(ht, i, j);
                }
            }
        }
    }
    //reads 2 bytes at a time decoding 2 messages into message 1 and 2 respectively
    //increment correct/incorrect based on the status decode returns
    while ((c = fgetc(inputp)) != EOF) {
        status = decode(ht, c, &msg1);
        totBytes++;
        if (status == HAM_ERR) {
            incorrect++;
        } else if (status == HAM_CORRECT) {
            correct++;
        }
        c = fgetc(inputp);
        status = decode(ht, c, &msg2);
        totBytes++;
        if (status == HAM_ERR) {
            incorrect++;
        } else if (status == HAM_CORRECT) {
            correct++;
        }
        fputc(pack_byte(msg2, msg1), fp);
    }
    bm_delete(&ht);
    if (input) {
        fclose(inputp);
    }
    if (output) {
        fclose(fp);
    }
    //prints stats if requested
    if (stats) {
        fprintf(stderr, "Total bytes processed: %.0f\n", totBytes);
        fprintf(stderr, "Uncorrected errors: %.0f\n", incorrect);
        fprintf(stderr, "Corrected errors: %d\n", correct);
        fprintf(stderr, "Error rate: %.5f\n", incorrect / totBytes);
    }
}
