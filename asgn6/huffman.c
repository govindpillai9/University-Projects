#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "defines.h"
#include "node.h"
#include "io.h"
#include "code.h"
#include "pq.h"
#include "stack.h"

Node *build_tree(uint64_t hist[static ALPHABET]) {
	PriorityQueue *pqueue = pq_create(ALPHABET);
	
}

void build_codes(Node *root, Code table[static ALPHABET]) {

}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {

}

void delete_tree(Node **root) {

}

