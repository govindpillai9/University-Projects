#include <stdint.h>
#include <stdio.h>
#include "quick.h"
#include "stack.h"
#include "queue.h"
#include "misc.h"
uint32_t max_stack_size = 0;
uint32_t max_queue_size = 0;
void q_increment_step(int *steppnt, int x) {
        *steppnt += 1;
        if(x == 1) {
                *steppnt = 0;
        }
}
static void swap(uint32_t *first, uint32_t *second) {
	q_increment_step(&moves, 0);
        uint32_t temp = *first;
	q_increment_step(&moves, 0);
        *first = *second;
	q_increment_step(&moves, 0);
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
                }
		q_increment_step(&comps, 0);
        }while(i < j);
        return j;
}




void quick_sort_stack(uint32_t *A, uint32_t n) {
	max_stack_size = 0;
	q_increment_step(&moves, 1);
	q_increment_step(&comps, 1);
	int64_t lo = 0;
	int64_t hi = n - 1;
	int64_t p = 0;
	Stack *s = stack_create(n+2);
	stack_push(s, lo);
	stack_push(s, hi);
	if(stack_size(s) > max_stack_size) {
		max_stack_size = stack_size(s);
	}
	while(!stack_empty(s)) {
		stack_pop(s, &hi);
		stack_pop(s, &lo);
		p = partition(A, lo, hi);
		if(lo < p) {
			stack_push(s, lo);
			stack_push(s, p);
			if(stack_size(s) > max_stack_size) {
				max_stack_size = stack_size(s);
			}
		}
		if(hi > p + 1) {
			stack_push(s, p+1);
			stack_push(s, hi);
			if(stack_size(s) > max_stack_size) {
				max_stack_size = stack_size(s);
			}
		}
	}
	stack_delete(&s);

}

void quick_sort_queue(uint32_t *A, uint32_t n) {
	max_queue_size = 0;
	q_increment_step(&moves, 1);
	q_increment_step(&comps, 1);
	int64_t lo = 0;
	int64_t hi = n - 1;
	int64_t p = 0;
	Queue *q = queue_create(10000);
	enqueue(q, lo);
	enqueue(q, hi);
	if(queue_size(q) > max_queue_size) {
		max_queue_size = queue_size(q);
	}
	while(!queue_empty(q)) {
		dequeue(q, &lo);
		dequeue(q, &hi);
		p = partition(A, lo, hi);
		if(lo < p) {
			enqueue(q, lo);
			enqueue(q, p);
			if(queue_size(q) > max_queue_size) {
				max_queue_size = queue_size(q);
			}
		}
		if(hi > p+1) {
			enqueue(q, p+1);
			enqueue(q, hi);
			if(queue_size(q) > max_queue_size) {
				max_queue_size = queue_size(q);
			}
		}
	}
	queue_delete(&q);
}


