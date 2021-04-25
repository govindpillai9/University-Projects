#include <stdint.h>
#include <stdio.h>
#include "quick.h"
#include "stack.h"
#include "queue.h"
uint32_t max_stack_size = 0;
uint32_t max_queue_size = 0;
int moves = 0;
int comps = 0;
void q_increment_step(int *steppnt, int x) {
        *steppnt += 1;
        if(x == 1) {
                *steppnt = 0;
        }
}
int quick_moves() {
        return moves;
}
int quick_comps() {
        return comps;
}
static void swap(uint32_t *first, uint32_t *second) {
        uint32_t temp = *first;
        *first = *second;
        *second = temp;
}

static int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
        uint32_t pivot = A[lo + ((hi - lo) / 2)];
        int64_t i = lo - 1;
        int64_t j = hi + 1;
        do {
                do {
                        i += 1;
			q_increment_step(&comps, 0);
                }while(A[i] < pivot);
                do {
                        j -= 1;
			q_increment_step(&comps, 0);
                }while(A[j] > pivot);
                if(i < j) {
                        swap(&A[i], &A[j]);
			q_increment_step(&moves, 0);
                }
		q_increment_step(&comps, 0);
        }while(i < j);
        return j;
}




void quick_sort_stack(uint32_t *A, uint32_t n) {
	q_increment_step(&moves, 1);
	q_increment_step(&comps, 1);
	int64_t lo = 0;
	int64_t hi = n - 1;
	int64_t p = 0;
	Stack *s = stack_create(n+2);
	stack_push(s, lo);
	q_increment_step(&moves, 0);
	stack_push(s, hi);
	q_increment_step(&moves, 0);
	while(!stack_empty(s)) {
		stack_pop(s, &hi);
		q_increment_step(&moves, 0);
		stack_pop(s, &lo);
		q_increment_step(&moves, 0);
		p = partition(A, lo, hi);
		if(lo < p) {
			stack_push(s, lo);
			q_increment_step(&moves, 0);
			stack_push(s, p);
			q_increment_step(&moves, 0);

		}
		if(hi > p + 1) {
			stack_push(s, p+1);
			q_increment_step(&moves, 0);
			stack_push(s, hi);
			q_increment_step(&moves, 0);

		}
	}

}

void quick_sort_queue(uint32_t *A, uint32_t n) {
	q_increment_step(&moves, 1);
	q_increment_step(&comps, 1);
	int64_t lo = 0;
	int64_t hi = n - 1;
	int64_t p = 0;
	Queue *q = queue_create(n+2);
	enqueue(q, lo);
	q_increment_step(&moves, 0);
	enqueue(q, hi);
	q_increment_step(&moves, 0);
	while(!queue_empty(q)) {
		dequeue(q, &lo);
		q_increment_step(&moves, 0);
		dequeue(q, &hi);
		q_increment_step(&moves, 0);
		p = partition(A, lo, hi);
		if(lo < p) {
			enqueue(q, lo);
			q_increment_step(&moves, 0);
			enqueue(q, p);
			q_increment_step(&moves, 0);
		}
		if(hi > p+1) {
			enqueue(q, p+1);
			q_increment_step(&moves, 0);
			enqueue(q, hi);
			q_increment_step(&moves, 0);
		}
	}
}


