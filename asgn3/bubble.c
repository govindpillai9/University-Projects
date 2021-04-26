#include "bubble.h"

#include "misc.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
static void swap(uint32_t *first, uint32_t *second);
//helps increment or set moves or comps to zero
void b_increment_step(int *steppnt, int x);
//checks if x is less than y while incrementing comps
static bool compare(uint32_t x, uint32_t y);
//based on python pseudocode from the lab doc
void bubble_sort(uint32_t *A, uint32_t n) {
    b_increment_step(&moves, 1);
    b_increment_step(&comps, 1);
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (uint32_t i = 1; i < n; i++) {
            if (compare(A[i], A[i - 1])) {
                swap(&A[i], &A[i - 1]);
                swapped = true;
            }
        }
        n -= 1;
    }
}
//swap function
static void swap(uint32_t *first, uint32_t *second) {
    b_increment_step(&moves, 0);
    uint32_t temp = *first;
    b_increment_step(&moves, 0);
    *first = *second;
    b_increment_step(&moves, 0);
    *second = temp;
}
static bool compare(uint32_t x, uint32_t y) {
    b_increment_step(&comps, 0);
    return x < y;
}
void b_increment_step(int *steppnt, int x) {
    *steppnt += 1;
    if (x == 1) {
        *steppnt = 0;
    }
}
