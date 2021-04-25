#include <stdio.h>
#include <stdint.h>
#include "gaps.h"
#include "shell.h"
int s_moves = 0;
int s_comps = 0;

void s_increment_step(int *steppnt, int x);
void shell_sort(uint32_t *A, uint32_t n) {
	s_increment_step(&s_moves, 1);
	s_increment_step(&s_comps, 1);
	uint32_t j = 0;
	uint32_t temp = 0;
	for(uint32_t x = 0; x < GAPS; x++) {
		for(uint32_t i = gaps[x]; i < n; i++) {
			j = i;
			temp = A[i];
			while((j >= gaps[x]) && (temp < A[j-gaps[x]])) {
				s_increment_step(&s_comps,0);
				A[j] = A[j-gaps[x]];
				s_increment_step(&s_moves,0);
				j -= gaps[x];
			}
			s_increment_step(&s_comps,0);
			A[j] = temp;
		}
	}
}
int shell_moves() {
        return s_moves;
}
int shell_comps() {
        return s_comps;
}

int main(void) {
        uint32_t bob[] = {35, 32, 30, 21, 11, 10, 7, 6, 5, 4, 3};
        uint32_t *pnt;
        pnt = bob;
        shell_sort(pnt, 11);
        for(int x = 0; x < 11; x++) {
                printf("%d ", bob[x]);
        }
        printf("%d moves", shell_moves());
        printf("%d comps", shell_comps());
}

void s_increment_step(int *steppnt, int x) {
        *steppnt += 1;
        if(x == 1) {
                *steppnt = 0;
        }
}

