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
#include "misc.h"
#define OPTIONS "hi:o:v"
uint8_t lower_nibble(uint8_t val) {
        return val & 0xF;
}

uint8_t upper_nibble(uint8_t val) {
        return val >> 4;
}

uint8_t pack_byte(uint8_t upper, uint8_t lower) {
        return (upper << 4) | (lower & 0xF);
}
int corrected;
int uncorrected;
int main(int argc, char **argv) {
	float totBytes = 0;
	uint32_t uncorrected = 0;
	uint32_t corrected = 0;
	uint8_t msg1 = 0;
	uint8_t msg2 = 0;
	HAM_STATUS status = 0;
        int c = 0;
        int opt = 0;
        bool help = false;
	bool stats = false;
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
			case 'v':
				stats = true;
				break;
                }
        }
        if(help) {
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

        BitMatrix *ht = bm_create(8,4);
        for(uint32_t i = 0; i < 8; i++) {
                for(uint32_t j = 0; j < 4; j++) {
                        if(i < 4) {
                                if(i == j) {
                                        bm_clr_bit(ht,i,j);
                                }else{
                                        bm_set_bit(ht,i,j);
                                }
                        }else{
                                if(i-j == 4) {
                                        bm_set_bit(ht,i,j);
                                }else{
                                        bm_clr_bit(ht,i,j);
                                }
                        }
                }
        }
        while((c = fgetc(inputp)) != EOF) {
		totBytes++;
                status  = decode(ht,c,&msg1);
		c = fgetc(inputp);
		totBytes++;
                status = decode(ht,c,&msg2);
		fputc(pack_byte(msg2,msg1), fp);

        }
	if(stats) {
		printf("Total bytes processed: %f\n",totBytes);
		printf("Uncorrected errors: %d\n", uncorrected);
		printf("Corrected errors: %d\n", corrected);
		printf("Error rate: %lf\n",uncorrected/totBytes);
	}


}
