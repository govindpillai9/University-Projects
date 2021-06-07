#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
} BloomFilter;

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return (bf);
}

void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
    return;
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t index = 0;
    index = hash(bf->primary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, index);
    index = hash(bf->secondary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, index);
    index = hash(bf->tertiary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, index);
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t index = 0;
    index = hash(bf->primary, oldspeak) % bf_size(bf);
    if (bv_get_bit(bf->filter, index) == 0) {
        return false;
    }
    index = hash(bf->secondary, oldspeak) % bf_size(bf);
    if (bv_get_bit(bf->filter, index) == 0) {
        return false;
    }
    index = hash(bf->tertiary, oldspeak) % bf_size(bf);
    if (bv_get_bit(bf->filter, index) == 0) {
        return false;
    }
    return true;
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i) == 1) {
            count++;
        }
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    printf("Bloom Filter: [");
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        printf("%d", bv_get_bit(bf->filter, i));
        if (i < bf_size(bf) - 1) {
            printf(", ");
        }
    }
    printf("]");
    printf("\n");
}
