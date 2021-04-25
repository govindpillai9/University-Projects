#include <stdio.h>
#include "bubble.h"
#include <stdint.h>
#include "misc.h"

static void swap(uint32_t *first, uint32_t *second);

void b_increment_step(int *steppnt, int x);
int bubble_moves();
int bubble_comps();

void bubble_sort(uint32_t *A, uint32_t n) {
	b_increment_step(&moves,1);
	b_increment_step(&comps,1);
	int swapped = 1;
	while(swapped == 1) {
		swapped = 0;
		for(uint32_t i = 1; i < n; i++) {
			if(A[i] < A[i-1]) {
				swap(&A[i], &A[i-1]);
				swapped = 1;
				b_increment_step(&moves,0);
			}
			b_increment_step(&comps,0);
		}	
	}
}

static void swap(uint32_t *first, uint32_t *second) {
	uint32_t temp = *first;
	*first = *second;
	*second = temp;
}
void b_increment_step(int *steppnt, int x) {
	*steppnt += 1;
	if(x == 1) {
		*steppnt = 0;
	}
}
