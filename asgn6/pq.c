#include "pq.h"

#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    Node **items;
} PriorityQueue;
//function creates priority queue
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (Node **) calloc(capacity, sizeof(Node));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}
//function deletes priority queue
void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        node_delete((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}
//function checks if the queue is empty
bool pq_empty(PriorityQueue *q) {
    return q->size == 0;
}
//function checks if the queue is full
bool pq_full(PriorityQueue *q) {
    return false;
    return q->size == q->capacity;
}
//function returns the size of the queue
uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}
//function enqueues a node onto the priority queue
bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }
    if (pq_empty(q)) {
        q->size += 1;
        q->items[q->tail] = n;
        q->tail = (q->tail + 1) % q->capacity;
    } else {
        uint32_t val = q->tail;
        while (val != q->head) {
            if (q->items[val - 1]->frequency > n->frequency) {
                q->items[val] = q->items[val - 1];
                val--;
            } else {
                q->items[val] = n;
                q->size += 1;
                q->tail = (q->tail + 1) % q->capacity;
                break;
            }
        }
        if (val == q->head) {
            q->items[val] = n;
            q->size += 1;
            q->tail = (q->tail + 1) % q->capacity;
        }
    }
    return true;
}
//function dequeues a node off the priority queue
bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    q->size -= 1;
    *n = q->items[q->head];
    q->head = (q->head + 1) % q->capacity;
    return true;
}
//function prints the queue
void pq_print(PriorityQueue *q) {
    printf("-----------------\n");
    printf("Queue: [");
    for (uint32_t i = q->head; i < q->tail; i++) {
        printf("(%d, %lu)", q->items[i]->symbol, q->items[i]->frequency);
        if (i != q->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Size: %d\n", q->size);
}
