#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "defines.h"
#include "huffman.h"
#include "node.h"
#include "io.h"
#include "code.h"
#include "pq.h"
#include "stack.h"

Node *build_tree(uint64_t hist[static ALPHABET]) {
	PriorityQueue *pqueue = pq_create(ALPHABET);
	for(uint8_t i = 0; i < 255; i++) {
		if(hist[i] != 0) {
			Node *n = node_create(i, hist[i]);
			enqueue(pqueue, n);
		}
	}
	Node *leftn = NULL;
	Node *rightn = NULL;
	while(pq_size(pqueue) > 1) {
		dequeue(pqueue,&leftn);
		dequeue(pqueue,&rightn);
		Node *join = node_join(leftn,rightn);
		enqueue(pqueue, join);
	}
	Node *root = NULL;
	dequeue(pqueue, &root);
	pq_delete(&pqueue);
	return root;

		
}
static bool initialized = false;
static Code c;
void build_codes(Node *root, Code table[static ALPHABET]) {
	if(!initialized) {
		c = code_init();
		initialized = true;
	}
	uint8_t *cptr = 0;
	if(root) {
		if(root->left == NULL && root->right == NULL) {
			table[root->symbol] = c;
		}else{
			code_push_bit(&c, 0);
			build_codes(root->left, table);
			code_pop_bit(&c, cptr);
			code_push_bit(&c, 1);
			build_codes(root->right, table);
			code_pop_bit(&c, cptr);
		}
	}
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
	Stack *s = stack_create(nbytes);
	Node *right = NULL;
	Node *left = NULL;
	Node *root = NULL;
	for(uint16_t i = 0; i < nbytes; i++) {
		if (tree[i] == 'L') {
			Node *n = node_create(tree[i+1],0);
		       stack_push(s, n);	
		       i++;
		}else{
			stack_pop(s, &right);
			stack_pop(s, &left);
			Node *joined = node_join(left, right);
			stack_push(s, joined);
		}    
	}
	stack_pop(s, &root);
        stack_delete(&s);
        return root;

}

void delete_tree(Node **root) {
	if((*root)->left == NULL && (*root)->right == NULL) {
        	node_delete(root);
	}else{
		delete_tree(&(*root)->left);
		delete_tree(&(*root)->right);
	}
}

