#include "shell.h"

#include "gaps.h"
#include "misc.h"

#include <stdint.h>
#include <stdio.h>

void s_increment_step(int *steppnt, int x);
void shell_sort(uint32_t *A, uint32_t n) {
    s_increment_step(&moves, 1);
    s_increment_step(&comps, 1);
    uint32_t j = 0;
    uint32_t temp = 0;
    for (uint32_t x = 0; x < GAPS; x++) {
        for (uint32_t i = gaps[x]; i < n; i++) {
            j = i;
            temp = A[i];
            s_increment_step(&moves, 0);
            while ((j >= gaps[x]) && (temp < A[j - gaps[x]])) {
                s_increment_step(&comps, 0);
                A[j] = A[j - gaps[x]];
                s_increment_step(&moves, 0);
                j -= gaps[x];
            }
            s_increment_step(&comps, 0);
            A[j] = temp;
            s_increment_step(&moves, 0);
        }
    }
}

void s_increment_step(int *steppnt, int x) {
    *steppnt += 1;
    if (x == 1) {
        *steppnt = 0;
    }
}
