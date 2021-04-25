#include <stdbool.h>
#include <stdint.h>
#include "queue.h"
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
typedef struct Queue {
	uint32_t head;
	uint32_t tail;
	uint32_t size;
	uint32_t capacity;
	int64_t *items;
}Queue;

Queue *queue_create(uint32_t capacity) {
	Queue *q = (Queue *)malloc(sizeof(Queue));
        if(q != NULL) {
                q->head = 0;
		q->tail = 0;
		q->size = 0;
                q->capacity = capacity;
                q->items = (int64_t *)calloc(capacity, sizeof(int64_t));
                if(q->items == NULL) {
                        free(q);
                        q = NULL;
                }
        }
        return q;


}

void queue_delete(Queue **q) {
	if(*q && (*q)->items) {
                free((*q)->items);
                free(*q);
                *q = NULL;
        }
        return;

}

bool queue_empty(Queue *q) {
	return q->size == 0;
}

bool queue_full(Queue *q) {
	return q->size == q->capacity;
}

uint32_t queue_size(Queue *q) {
	return q->size;
}

bool enqueue(Queue *q, int64_t x) {
	if(queue_full(q)) {
		return false;
	}
	q->size += 1;
	q->items[q->tail] = x;
	q->tail = (q->tail+1) % q->capacity;
	return true;
}

bool dequeue(Queue *q, int64_t *x) {
	if(queue_empty(q)) {
		return false;
	}
	q->size -= 1;
	*x = q->items[q->head];
	q->head = (q->head+1) % q->capacity;
	return true;
}

void queue_print(Queue *q) {
	printf("[");
        for(uint32_t i = 0; i < q->size; i++) {
                printf("%" PRId64, q->items[i]);
                printf(", ");
        }
        printf("]");

}


